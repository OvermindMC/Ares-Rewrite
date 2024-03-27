#pragma once

#include "EnTT/EnTT.h"
#include "Math/Vector.h"
#include "Math/Random.h"
#include "Macro/Class.h"
#include "MapRef/MapRef.h"

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
};