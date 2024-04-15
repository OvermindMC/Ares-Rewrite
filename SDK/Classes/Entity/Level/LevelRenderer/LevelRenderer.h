#pragma once

#include "../../../../../Mem/Math/Vector.h"
#include "../../../../../Mem/Macro/Class.h"

class LevelRendererPlayer {
public:
    BUILD_ACCESS(Vec3<float>, eyePos, 0x5FC);
};

class LevelRenderer {
public:
    auto getRenderPlayer(void) -> LevelRendererPlayer* {
        return *(LevelRendererPlayer**)((unsigned long long)(this) + 0x308);
    };
public:
    AS_FIELD(LevelRendererPlayer*, renderPlayer, getRenderPlayer);
};