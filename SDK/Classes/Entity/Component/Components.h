#pragma once

#include "../../../../Mem/Mem.h"

struct StateVectorComponent {
    Vec3 position;
    Vec3 oldPosition;
    Vec3 positionDelta;
};