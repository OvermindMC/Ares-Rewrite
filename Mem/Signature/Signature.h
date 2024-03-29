#pragma once

#include <assert.h>
#include <libhat/Scanner.hpp>

class Signature {
public:
    enum class SearchType { Default = 0, VTable = 1, Ref = 2 };
private:
    const char* pattern = nullptr;
    uintptr_t address = 0x0;
    bool searched = false;
public:
    Signature(const char* signature_pattern) : pattern(signature_pattern) {};
public:
    auto get(SearchType) -> void*;
};