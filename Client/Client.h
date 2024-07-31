#pragma once

#include "../SDK/Minecraft.h"
#include "../Utils/Utils.h"
#include "../Mem/Mem.h"

#include "Result/Result.h"
#include "Version/Version.h"

class Manager;

class Client {
public:
    Client(const std::string&, const Version&);
    ~Client();

    std::string getName() const;
    Version getVer() const;

    PTR_ACCESS(Manager*, mgr, miPtr);
private:
    Manager* miPtr = nullptr;
    
    const std::string clientName;
    const Version clientVer;
};