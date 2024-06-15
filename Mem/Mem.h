#pragma once

#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <winsock2.h>
#pragma comment(lib, "Ws2_32.lib")

#include "EnTT/EnTT.h"
#include "Math/Vector.h"
#include "Math/Random.h"
#include "Macro/Class.h"
#include "MapRef/MapRef.h"
#include "Signature/Signature.h"

#undef min
#undef max
#include <algorithm>

#include <MinHook.h>
#include <Windows.h>
#include <Psapi.h>
#include <vector>
#include <bitset>
#include <variant>
#include <assert.h>
#include <atomic>

#include <nlohmann/json.hpp>
using json = nlohmann::json;

class Mem {
public:
    static auto getDll(void) -> HMODULE;
public:
    static auto findSig(const char* pattern) -> std::unique_ptr<Signature>;
    static auto getNestedPtr(uintptr_t baseOffset, std::vector<unsigned int> offsets, bool use_exact_base_offset = false) -> void*;
public:
    template<unsigned int I, typename Type, typename... TArgs>
	static inline auto callVFunc(void* ptr, TArgs... args) -> Type {
		using Fn = Type(__fastcall*)(void*, decltype(args)...);
		return (*static_cast<Fn**>((void*)ptr))[I]((void*)ptr, args...);
	};
};