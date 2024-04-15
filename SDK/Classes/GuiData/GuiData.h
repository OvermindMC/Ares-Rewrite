#pragma once

#include "../../../Mem/Math/Vector.h"
#include "../../../Mem/Macro/Class.h"

class GuiData {
public:
    BUILD_ACCESS(float, uiScale, 0x4C);
    BUILD_ACCESS(Vec2<float>, windowSize, 0x30);
    BUILD_ACCESS(Vec2<float>, windowSizeScaled, 0x30);
};