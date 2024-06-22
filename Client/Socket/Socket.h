#pragma once

#include "../../Mem/Mem.h"
#include "../../Utils/Utils.h"
#include "../../SDK/Minecraft.h"

class Client;
class Version;
class AresUser;

class SocketLayer {
private:
    Client* client_ptr = nullptr;
    AresUser* aresUser = nullptr;

    WSADATA wsaData;
    sockaddr_in serverAddr;
    SOCKET clientSocket = INVALID_SOCKET;
public:
    SocketLayer(Client* raw_client_ptr);
    ~SocketLayer(void);

    auto tryConnect(void) -> void;

    auto start(void) -> void;
    auto stop(void) -> void;
    auto run(void) -> void;

    auto isConnected(void) -> bool;
    auto sendToStream(json&) -> json;

    std::thread socketThread;
    std::atomic<bool> running;

    PTR_ACCESS(Client*, client, client_ptr);
    PTR_ACCESS(AresUser*, user, aresUser);
};

class AresUser {
private:
    SocketLayer* socket_layer = nullptr;
public:
    class AresVersion {
        private:
            std::string version;
            json patchnotes = {};
        public:
            AresVersion(std::string latest_ver, json patch_notes) : version(latest_ver), patchnotes(patch_notes) {};

            auto isValid(void) -> bool {
                return version.length() > 0;
            };

            auto get(void) -> std::pair<const std::string&, const json&> {
                return std::pair<const std::string&, const json&>(this->version, this->patchnotes);
            };
    };

    AresUser(SocketLayer* socket);
    AresVersion aresVer;

    auto fetchUpdate(void) -> void;
    auto hasUpdate(void) -> bool;
};