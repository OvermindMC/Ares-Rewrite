#include "LuaBindings.h"

void LuaBindings::registerFunctions(lua_State* L) {
    lua_register(L, "logToConsole", logToConsole);
};

int LuaBindings::logToConsole(lua_State* L) {
    if (lua_gettop(L) != 1 || !lua_isstring(L, 1)) {
        lua_pushstring(L, "Invalid arguments. Expected a single string.");
        lua_error(L);
        return 0;
    };

    const char* message = lua_tostring(L, 1);
    Debugger::log(message);

    return 0;
};