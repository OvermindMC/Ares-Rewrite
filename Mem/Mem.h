#pragma once

#include <Windows.h>
#include <assert.h>
#include <sstream>

class Mem {
public:
    static auto getDll(void) -> HMODULE;
};