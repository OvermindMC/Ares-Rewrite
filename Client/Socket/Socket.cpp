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
            };
        };
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
        Sleep(1000);
    };
};