#include "Socket.h"
#include "../Client.h"

SocketLayer::SocketLayer(Client* client_ptr) : client(client_ptr) {
    auto ip = std::string("132.145.76.173");
    int port = 8000;

    this->serverAddr.sin_family = AF_INET;
    this->serverAddr.sin_port = htons(port);
    this->serverAddr.sin_addr.s_addr = inet_addr(ip.c_str());

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

    auto success = this->clientSocket != INVALID_SOCKET;
    this->client->addNotif("Ares Server", success ? "Connected!" : "Failed To Connect!", success ? 1000 : 5000, !success);
};

SocketLayer::~SocketLayer() {
    if (this->clientSocket != INVALID_SOCKET) {
        closesocket(this->clientSocket);
        WSACleanup();
    };
};