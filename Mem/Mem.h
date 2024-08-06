#pragma once

#include <libhat/Scanner.hpp>
#include <type_traits>
#include <functional>
#include <MinHook.h>
#include <Windows.h>
#include <assert.h>
#include <utility>
#include <Psapi.h>
#include <vector>
#include <memory>
#include <map>

#include "AABB/AABB.h"
#include "Vector/Vec.h"
#include "Macro/Class.h"
#include "EnTT/EnTT.h"

#define PI 3.14159265358979323846
const float DEG_TO_RAD = PI / 180.0f;
const float RAD_TO_DEG = 180.0f / PI;

class Mem {
public:
    static HMODULE getDll();
    static void* resPtr(uintptr_t baseOffset, const std::vector<unsigned int>& offsets, bool useGameBase = false);
    static void* getSig(std::string_view search);
    static void* getRef(std::string_view search, int off = 0);

    template<typename RetType, typename... Args>
    static inline RetType CallVFunc(void* ptr, unsigned int index, Args... args) {
        using Func = RetType(__fastcall*)(void*, Args...);
        Func function = (*static_cast<Func**>(ptr))[index];
        return function(ptr, args...);
    };
};