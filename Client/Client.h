#pragma once

#include "../Mem/Mem.h"
#include "../Utils/Utils.h"

#include "Version/Version.h"

class Client {
public:
    Client(const char* client_name) : name(client_name ? client_name : "") {}
    ~Client(void) {};
public:
    auto getName(void) -> std::string;
    auto getVersion(void) -> Version;
private:
    std::string name;
    Version version = Version(1, 0, 0);
private:
    bool isRunning = false;
};