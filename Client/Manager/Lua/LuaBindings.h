#pragma once

#include "../../../Utils/Utils.h"
#include "../../../Mem/Mem.h"

class LuaBindings {
public:
    static void registerFunctions(lua_State* L);
private:
    static int logToConsole(lua_State* L);
};