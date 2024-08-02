#pragma once

#include "LuaBindings.h"

class Manager;

class LuaScripting {
public:
    LuaScripting(Manager*);
    ~LuaScripting();

    void initializeLua();
    bool loadScript(const std::string& scriptPath);
    void runScript(const std::string& script);
    void registerFunction(const std::string& name, lua_CFunction func);

private:
    Manager* miPtr;
    lua_State* L;
};