#pragma once

#include "../../../../../Mem/Mem.h"

class BlockLegacy {
public:
    BUILD_ACCESS(std::string, tile, 0x28);
    BUILD_ACCESS(std::string, name, 0x50);
};

class Block {
public:
    BUILD_ACCESS(BlockLegacy*, legacy, 0x30);
    BUILD_ACCESS(uint64_t, runtimeId, 0xC4);
};