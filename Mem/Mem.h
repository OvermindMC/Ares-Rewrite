#pragma once

#include <libhat/MemoryProtector.hpp>
#include <libhat/Scanner.hpp>
#include <libhat/Access.hpp>
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
    static void* resPtr(uintptr_t baseOffset, const std::vector<unsigned int>& offsets, bool useGameBase = false);
    static void* getSig(std::string_view search);
    static void* getRef(std::string_view search, int off = 0);
};