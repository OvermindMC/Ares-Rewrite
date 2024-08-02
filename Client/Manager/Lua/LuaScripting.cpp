#include "LuaScripting.h"

LuaScripting::LuaScripting(Manager* mgr) : miPtr(mgr), L(luaL_newstate()) {
    luaL_openlibs(L);
    initializeLua();
};

LuaScripting::~LuaScripting() {
    lua_close(L);
};

void LuaScripting::initializeLua() {
    LuaBindings::registerFunctions(L);
};

bool LuaScripting::loadScript(const std::string& scriptPath) {
    if (luaL_dofile(L, scriptPath.c_str()) != LUA_OK) {
        std::cerr << "Error loading Lua script: " << lua_tostring(L, -1) << std::endl;
        lua_pop(L, 1);
        return false;
    };
    return true;
};

void LuaScripting::runScript(const std::string& script) {
    if (luaL_dostring(L, script.c_str()) != LUA_OK) {
        std::cerr << "Error running Lua script: " << lua_tostring(L, -1) << std::endl;
        lua_pop(L, 1);
    };
};

void LuaScripting::registerFunction(const std::string& name, lua_CFunction func) {
    lua_register(L, name.c_str(), func);
};