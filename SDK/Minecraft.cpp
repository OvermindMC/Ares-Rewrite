#include "Minecraft.h"

auto MC::getClientInstance(void) -> ClientInstance* {

    static auto sig = Mem::findSig("48 89 0D ? ? ? ? 48 89 0D ? ? ? ? 48 85 C0 74 0F 48 8B C8 E8 ? ? ? ? 48 8B 0D ? ? ? ? 48 85 C9 74 09 48 83 C4 28 E9 ? ? ? ? 48 83 C4 28 C3 CC CC CC CC CC CC CC CC CC CC CC CC CC CC 48 83 EC 28 48 8D 0D ? ? ? ? FF 15 ? ? ? ? 48 8B 0D ? ? ? ? 48 85 C9 74 09 48 83 C4 28 E9 ? ? ? ? 48 83 C4 28 C3 CC CC CC CC CC 48 83 EC 28 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8D 0D ? ? ? ? 48 83 C4 28 E9 ? ? ? ? 40 53 48 83 EC 20 48 8B 0D ? ? ? ? 48 8B 59 08 80 7B 19 00 75 4E 48 89 7C 24 ? 0F 1F 40 00 4C 8B 43 10 48 8D 15 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8B FB 48 8B 1B 48 8D 4F 20");
    static auto clientinstance_raw_ptr = Mem::getNestedPtr((uintptr_t)sig->get(Signature::SearchType::VTable), { 0x0, 0x58, 0x0, 0x0 }, true);
    
    return (ClientInstance*)(clientinstance_raw_ptr);

};