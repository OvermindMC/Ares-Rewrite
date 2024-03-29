#include "Mem.h"
#include <libhat/Scanner.hpp>

auto Mem::getDll(void) -> HMODULE {

    MEMORY_BASIC_INFORMATION info;
    size_t len = VirtualQueryEx(GetCurrentProcess(), (void*)getDll, &info, sizeof(info));
    assert(len == sizeof(info));
    return len ? (HMODULE)info.AllocationBase : NULL;

};

auto Mem::findSig(const char* pattern) -> Signature* {

    return new Signature(pattern);

};

auto Mem::getNestedPtr(uintptr_t baseOffset, std::vector<unsigned int> offsets, bool use_exact_base_offset) -> void* {

    auto currResult = (use_exact_base_offset ? baseOffset : (uintptr_t)(GetModuleHandleA("Minecraft.Windows.exe")) + baseOffset);

    for (auto offset : offsets) {
        try {
            if (currResult == 0)
                return nullptr;

            currResult = *(uintptr_t*)currResult;
            currResult += offset;
        }
        catch (...) {
            return nullptr;
        };
    };

    return (IsBadReadPtr(reinterpret_cast<void*>(currResult), sizeof(void*)) == 0 ? (void*)currResult : nullptr);

};