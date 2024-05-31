#pragma once

#include "../Packet.h"

class MovePlayerPacket : public Packet {
public:
    enum class PositionMode : UCHAR {
        Normal      = 0,
        Respawn     = 1,
        Teleport    = 2,
        OnlyHeadRot = 3,
    };
    enum class TeleportationCause : int {
        Unknown = 0,
        Projectile  = 0x1,
        ChorusFruit = 0x2,
        Command     = 0x3,
        Behavior    = 0x4,
        Count       = 0x5,
    };
public:
    uint64_t runtimeId;
    Vec3<float> position;
    Vec2<float> bodyRot;
    float headYaw;
    PositionMode resetPosition;
    bool onGround;
private:
    char padd[6];
public:
    uint64_t ridingRuntimeId;
    TeleportationCause teleportCause;
    uint32_t sourceEntityType;
    uint64_t tick;
};

template<PacketID>
struct PacketTypeMap;

template<>
struct PacketTypeMap<PacketID::Move_Player> {
    using type = MovePlayerPacket;
};