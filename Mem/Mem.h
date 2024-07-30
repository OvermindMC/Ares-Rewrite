#pragma once

#include <MinHook.h>
#include <Windows.h>
#include <assert.h>
#include <Psapi.h>
#include <vector>
#include <memory>
#include <map>

#include "Vector/Vec.h"
#include "Macro/Class.h"

class Mem {
public:
    static HMODULE getDll();
};