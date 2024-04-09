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

/* Runtime Attributes */

private:
    bool _isRunning = false;
    Manager* mgr_raw_ptr = nullptr;

public:
    PTR_ACCESS(Manager*, mgr, mgr_raw_ptr);

/* Runtime Methods */
public:
    auto init(void) -> void;
public:
    auto isRunning(void) -> bool;
    auto stop(void) -> void;
};