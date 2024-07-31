#include "Mem.h"

HMODULE Mem::getDll() {
    MEMORY_BASIC_INFORMATION info;
    size_t len = VirtualQueryEx(GetCurrentProcess(), reinterpret_cast<void*>(getDll), &info, sizeof(info));
    assert(len == sizeof(info));
    return len ? static_cast<HMODULE>(info.AllocationBase) : NULL;
};

void* Mem::resPtr(uintptr_t baseOffset, const std::vector<unsigned int>& offsets, bool useGameBase) {
    uintptr_t current = baseOffset;

    if (useGameBase) {
        HMODULE moduleHandle = GetModuleHandle(nullptr);
        if (!moduleHandle) {
            return nullptr;
        };
        current = reinterpret_cast<uintptr_t>(moduleHandle) + baseOffset;
    };

    for (const auto& offset : offsets) {
        if (current == 0) {
            return nullptr;
        };

        current = *reinterpret_cast<uintptr_t*>(current);
        current += offset;
    };

    return reinterpret_cast<void*>(current);
};

void* Mem::getSig(std::string_view search) {
    hat::result parsed = hat::parse_signature(search);
    assert(parsed.has_value());

    hat::scan_result result = hat::find_pattern(parsed.value(), ".text");
    return result.has_result() ? (void*)result.get() : nullptr;
};

void* Mem::getRef(std::string_view search, int offset) {
    uintptr_t addr = reinterpret_cast<uintptr_t>(Mem::getSig(search));
    
    if (*reinterpret_cast<uint8_t*>(addr) != 0xE8) {
        return nullptr;
    };

    int32_t relOff = *reinterpret_cast<int32_t*>(addr + 1);
    return reinterpret_cast<void*>(addr + relOff + 5 + offset);
};