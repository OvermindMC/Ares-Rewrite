#include "Socket.h"
#include "../Client.h"

SocketLayer::SocketLayer(Client* client_ptr) : client(client_ptr) {
    auto ip = std::string("132.145.76.173");
    int port = 8000;

    this->serverAddr.sin_family = AF_INET;
    this->serverAddr.sin_port = htons(port);
    this->serverAddr.sin_addr.s_addr = inet_addr(ip.c_str());

    this->tryConnect();

    auto success = this->clientSocket != INVALID_SOCKET;
    this->client->addNotif("Ares Server", success ? "Connected!" : "Failed To Connect!", success ? 1000 : 5000, !success);
};

SocketLayer::~SocketLayer() {
    this->stop();
    if (this->clientSocket != INVALID_SOCKET) {
        closesocket(this->clientSocket);
        WSACleanup();
    };
};

auto SocketLayer::tryConnect(void) -> void {
    if (WSAStartup(MAKEWORD(2, 2), &this->wsaData) == 0) {
        this->clientSocket = socket(AF_INET, SOCK_STREAM, 0);
        if (this->clientSocket == INVALID_SOCKET) {
            WSACleanup();
        } else {
            if (connect(this->clientSocket, reinterpret_cast<sockaddr*>(&serverAddr), sizeof(serverAddr)) == SOCKET_ERROR) {
                closesocket(this->clientSocket);
                this->clientSocket = INVALID_SOCKET;
                WSACleanup();
            } else {
                auto curr_ver = this->client->getVersion().get();
                json data = {
                    {"version", curr_ver}, {"type", "version"}
                };
                auto result = this->sendToStream(data);
                Debugger::log(result.dump());

                if(result.contains("data") && result["data"].contains("version") && result["data"].contains("patch_notes")) {
                    auto latest_ver = Version(result["data"]["version"].get<std::string>());
                    
                    if(latest_ver > curr_ver) {
                        this->client->addNotif("Update", std::string(this->client->getName() + " v" + latest_ver.get()), 5000, true);
                    };
                };
            };
        };
    };
};

auto SocketLayer::start(void) -> void {
    if(this->running)
        return;
    
    this->running = true;
    this->socketThread = std::thread(&SocketLayer::run, this);
};

auto SocketLayer::stop(void) -> void {
    if(!this->running)
        return;
    
    this->running = false;

    if (clientSocket != INVALID_SOCKET) {
        closesocket(clientSocket);
        this->clientSocket = INVALID_SOCKET;
        WSACleanup();
    };
    
    if(this->socketThread.joinable())
        this->socketThread.join();
};

auto SocketLayer::run(void) -> void {
    while(this->running) {
        if(this->isConnected()) {
            //
        } else {
            this->tryConnect();

            if(this->clientSocket != INVALID_SOCKET)
                this->client->addNotif("Ares Server", "Connected!", 1000);
        };
        Sleep(100);
    };
};

auto SocketLayer::isConnected(void) -> bool {
    if (clientSocket == INVALID_SOCKET) {
        return false;
    };

    WSAEVENT event = WSACreateEvent();
    if (event == WSA_INVALID_EVENT) {
        Debugger::log("WSACreateEvent failed");
        return false;
    };

    if (WSAEventSelect(clientSocket, event, FD_READ | FD_CLOSE) == SOCKET_ERROR) {
        Debugger::log("WSAEventSelect failed");
        WSACloseEvent(event);
        return false;
    };

    timeval timeout;
    timeout.tv_sec = 0;
    timeout.tv_usec = 100;

    fd_set readSet;
    FD_ZERO(&readSet);
    FD_SET(clientSocket, &readSet);

    int selectResult = select(0, &readSet, NULL, NULL, &timeout);
    if (selectResult == SOCKET_ERROR) {
        Debugger::log("WSAEventSelect select failed");
        WSACloseEvent(event);
        return false;
    } else if (selectResult == 0) {
        WSACloseEvent(event);
        return true;
    };

    if (FD_ISSET(clientSocket, &readSet)) {
        char buffer;
        int result = recv(clientSocket, &buffer, 1, MSG_PEEK);
        if (result == SOCKET_ERROR) {
            int error = WSAGetLastError();
            Debugger::log("Socket Client recv failed: " + std::to_string(error));
            WSACloseEvent(event);
            return false;
        } else if (result == 0) {
            this->client->addNotif("Ares Server", "Disconnected!", 5000, true);
            WSACloseEvent(event);

            closesocket(clientSocket);
            this->clientSocket = INVALID_SOCKET;
            WSACleanup();

            return false;
        };
        WSACloseEvent(event);
        return true;
    };

    WSACloseEvent(event);
    return false;
};

auto SocketLayer::sendToStream(json& data) -> json {
    WSAEVENT event = WSACreateEvent();
    json result = { {"success", false} };

    if (event == WSA_INVALID_EVENT) {
        Debugger::log("WSACreateEvent failed");
        return result;
    };

    if (WSAEventSelect(clientSocket, event, FD_READ | FD_WRITE | FD_CLOSE) == SOCKET_ERROR) {
        Debugger::log("WSAEventSelect failed");
        WSACloseEvent(event);
        return result;
    };

    auto dump = data.dump();

    int bytesSent = send(clientSocket, dump.c_str(), static_cast<int>(dump.length()), 0);
    if (bytesSent == SOCKET_ERROR) {
        Debugger::log("Send failed: " + std::to_string(WSAGetLastError()));
        WSACloseEvent(event);
        return result;
    };

    DWORD resultFlags = WSA_WAIT_EVENT_0;
    bool eventOccurred = false;

    while (!eventOccurred) {
        DWORD waitResult = WSAWaitForMultipleEvents(1, &event, FALSE, 5000, FALSE); // Timeout after 5 seconds
        if (waitResult == WSA_WAIT_FAILED) {
            Debugger::log("WSAWaitForMultipleEvents failed");
            break;
        } else if (waitResult == WSA_WAIT_TIMEOUT) {
            Debugger::log("Timeout waiting for socket event");
            break;
        };

        WSANETWORKEVENTS networkEvents;
        ZeroMemory(&networkEvents, sizeof(networkEvents));

        if (WSAEnumNetworkEvents(clientSocket, event, &networkEvents) == SOCKET_ERROR) {
            Debugger::log("WSAEnumNetworkEvents failed");
            break;
        };

        if (networkEvents.lNetworkEvents & FD_READ) {
            char buffer[1024];
            int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);

            if (bytesReceived == SOCKET_ERROR || bytesReceived == 0) {
                Debugger::log("Recv failed or connection closed");
                break;
            };

            buffer[bytesReceived] = '\0';

            try {
                result = json::parse(std::string(buffer));
                result["success"] = true;
            } catch (const std::exception& e) {
                Debugger::log("JSON parsing error: " + std::string(e.what()));
            };

            eventOccurred = true;
            break;
        };

        if (networkEvents.lNetworkEvents & FD_CLOSE) {
            Debugger::log("Socket closed by server");
            break;
        };
    };

    WSACloseEvent(event);
    return result;
};