#pragma once

#include "../Manager.h"

template<typename Type, typename... Args>
class Hook {
private:
    Manager* mgr_raw_ptr = nullptr;
public:
    PTR_ACCESS(Manager*, mgr, mgr_raw_ptr);
public:
    using Func = Type(__thiscall*)(Args...); /* Declare return type and arguments for detour function */
    Func _Func = (Func)nullptr; /* Pointer declaration of original function for calling original function after our existing implementation */
public:
    static inline std::function<Type(Args...)> callback = [&](Args... args) -> Type { return Type{}; }; /* Declare callback with type, arguments */
public:
    static auto detourCallback(Args... arguments) -> Type {
        return callback ? callback(arguments...) : Type{}; /* If T (return type) isn't void, return empty initialization */
    };
private:
    const char* _name = nullptr;
    void* _addr = nullptr;
public:
    PTR_ACCESS(const char*, name, _name);
    PTR_ACCESS(void*, address, _addr);
public:
    Hook(Manager* mgr, const char* name, void* addr, std::function<Type(Args...)> cb) : mgr_raw_ptr(mgr), _name(name), _addr(addr) {

        this->callback = cb;
        
        if(MH_CreateHook(addr, &detourCallback, reinterpret_cast<LPVOID*>(&_Func)) != MH_OK) {
            Debugger::log("Failed to initialize hook <" + std::string(name) + ">");
        } else {
            std::ostringstream o;
            o << std::hex << addr;

            Debugger::log("Successfully initialized hook <" + std::string(name) + ":" + o.str() + ">");
            
            if(mgr->registerHook(this)) {
                MH_EnableHook(addr);
            } else {
                Debugger::log("Failed to enable hook <" + std::string(name) + ":" + o.str() + ">");
            };
        };

    };
    ~Hook(void) {
        MH_DisableHook(this->_addr);
        Debugger::log("Deleted " + std::string(this->_name));
        Sleep(1000);
    };
};