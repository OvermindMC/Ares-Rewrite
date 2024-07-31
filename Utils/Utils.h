#pragma once

#include "Debug/Debugger.h"

class Utils {
public:
    template<typename RetType, typename... Args>
    static inline RetType CallVFunc(void* ptr, unsigned int index, Args... args) {
        using Func = RetType(__fastcall*)(void*, Args...);
        Func function = (*static_cast<Func**>(ptr))[index];
        return function(ptr, args...);
    };
};