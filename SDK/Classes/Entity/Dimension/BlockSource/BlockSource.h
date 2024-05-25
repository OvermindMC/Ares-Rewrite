#pragma once

#include "Block.h"

class BlockSource {
public:
    auto getBlock(Vec3<int>* pos) -> Block* {
        return Mem::callVFunc<2, Block*, Vec3<int>*>(this, pos);
    };

    auto getBlock(Vec3<int> pos) -> Block* {
        return this->getBlock(&pos);
    };
};