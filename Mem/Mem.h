#pragma once

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

class Mem {
public:
    static auto getDll(void) -> HMODULE;
public:
    static auto findSig(const char* pattern) -> std::unique_ptr<Signature>;
    static auto getNestedPtr(uintptr_t baseOffset, std::vector<unsigned int> offsets, bool use_exact_base_offset = false) -> void*;
};