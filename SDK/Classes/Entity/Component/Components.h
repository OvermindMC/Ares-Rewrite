#pragma once

#include "Flags.h"

class ActorOwnerComponent {
public:
    class Actor* actor;
};

struct RuntimeIDComponent {
    uint64_t runtimeId;
};

struct StateVectorComponent {
    Vec3 position;
    Vec3 oldPosition;
    Vec3 positionDelta;
};

struct MaxAutoStepComponent {
    float stepHeight;
};

struct MovementSpeedComponent {
    float speed;
};

struct SwimSpeedMultiplierComponent {
    float speed;
};

struct ActorSetPositionRequestComponent {
    Vec3 position;
};

struct AABBShapeComponent {
    AABB AABB;
    Vec2 radius;
};

struct BlockMovementSlowdownMultiplierComponent {};
struct OnGroundFlagComponent {};
struct ItemInUseComponent {};