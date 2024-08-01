#pragma once

#include "../Manager.h"

template<typename Type, typename... Args>
class Hook {
public:
    using Func = Type(__thiscall*)(Args...);
    Func _Func = nullptr;

    static inline std::function<Type(Args...)> callback = [&](Args... args) -> Type { return Type{}; };
    static Type detourCallback(Args... args) {
        return callback ? callback(args...) : Type{};
    };

    Hook(Manager* mgr, std::string name, void* target, std::function<Type(Args...)> cb)
        : miPtr(mgr), hName(name), tAddr(target) {
        this->callback = cb;

        std::ostringstream ss;
        ss << name << ":" << std::hex << target;

        if(MH_CreateHook(target, &detourCallback, reinterpret_cast<LPVOID*>(&_Func)) == MH_OK) {
            MH_EnableHook(target);
            Debugger::log("Enabled Hook <" + ss.str() + ">");
        } else {
            Debugger::log("Hook Failed <" + ss.str() + ">");
        };
    };

    ~Hook() {
        MH_DisableHook(this->tAddr);
        this->tAddr = nullptr;
    };

    PTR_ACCESS(Manager*, mgr, miPtr);
    std::string getName() const { return this->hName; };
private:
    Manager* miPtr = nullptr;
    void* tAddr = nullptr;
    std::string hName;
};