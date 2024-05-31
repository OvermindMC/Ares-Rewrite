#pragma once

#include "Flags.h"

class ActorOwnerComponent {
public:
    class Actor* actor;
};

struct RuntimeIDComponent
{
    unsigned long long runtimeId;
};

struct ActorUniqueIDComponent 
{
    unsigned long long uniqueId;
};

struct ActorGameTypeComponent {
    enum GameType type;
};

struct ActorTypeComponent {
    uint8_t typeId;
};

struct MaxAutoStepComponent {
    float maxAutoStep;
};

struct FlySpeedComponent {
    float flightSpeed;
};

struct MovementSpeedComponent {
    float speed;
};

struct SwimSpeedMultiplierComponent {
    float speed;
};

struct RenderPositionComponent {
    Vec3<float> renderPos;
};

struct ActorSetPositionRequestComponent {
    Vec3<float> position;
};

struct StateVectorComponent {
    Vec3<float> position;
    Vec3<float> oldPosition;
    Vec3<float> positionDelta;
};

struct ActorRotationComponent {
    Vec2<float> rotation;
    Vec2<float> rotationPrev;
};

struct AABBShapeComponent {
    AABB<float> AABB;
    Vec2<float> radius;
};

struct AbilitiesComponent {
    //
};

struct BlockMovementSlowdownMultiplierComponent {
    //
};

struct ItemInUseComponent {
    //
};