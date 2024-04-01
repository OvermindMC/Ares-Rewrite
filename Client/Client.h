#pragma once

#include "../Mem/Mem.h"
#include "../Utils/Utils.h"
#include "../SDK/Minecraft.h"

#include "Version/Version.h"

class Manager; /* Forward Declaration */

/* Client Class */

class Client {
/* Constructor, Deconstructor */

public:
    Client(const char* client_name);
    ~Client(void);
    
/* Client Name, Client Version */

public:
    auto getName(void) -> std::string;
    auto getVersion(void) -> Version;
private:
    std::string name;
    Version version = Version(1, 0, 0);

/* Runtime */

private:
    bool _isRunning = false;
    Manager* mgr = nullptr;

public:
    auto init(void) -> void;
    auto isRunning(void) -> bool;
};