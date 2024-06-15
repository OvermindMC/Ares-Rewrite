#pragma once

#include "../../Mem/Mem.h"
#include "../../Utils/Utils.h"
#include "../../SDK/Minecraft.h"

class Client;

class SocketLayer {
private:
    Client* client = nullptr;

    WSADATA wsaData;
    sockaddr_in serverAddr;
    SOCKET clientSocket = INVALID_SOCKET;
public:
    SocketLayer(Client* client_ptr);
    ~SocketLayer(void);
};