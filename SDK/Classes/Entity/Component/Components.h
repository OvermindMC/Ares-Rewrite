#pragma once

#include "Flags.h"

struct RuntimeIDComponent {
    uint64_t runtimeId;
};

struct StateVectorComponent {
    Vec3 position;
    Vec3 oldPosition;
    Vec3 positionDelta;
};

struct OnGroundFlagComponent {
    //
};

struct BlockMovementSlowdownMultiplierComponent {
    //
};

struct ItemInUseComponent {
    //
};