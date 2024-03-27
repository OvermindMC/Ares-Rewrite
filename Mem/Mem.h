#pragma once

#include <Windows.h>
#include <assert.h>
#include <sstream>
#include <vector>
#include <map>

class Mem {
public:
    static auto getDll(void) -> HMODULE;
};