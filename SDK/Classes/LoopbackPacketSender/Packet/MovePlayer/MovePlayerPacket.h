#pragma once

#include "../Packet.h"

class MovePlayerPacket : public Packet {
private:
    char pad[0xC0];
public:
    BUILD_ACCESS(uint64_t, runtimeId, 0x30);
    BUILD_ACCESS(Vec3<float>, position, 0x38);
    BUILD_ACCESS(Vec2<float>, bodyRot, 0x44);
    BUILD_ACCESS(float, headYaw, 0x4C);
    BUILD_ACCESS(bool, onGround, 0x51);
    BUILD_ACCESS(uint64_t, ridingRuntimeId, 0x58);
    BUILD_ACCESS(uint64_t, tick, 0x68);
};

template<PacketID>
struct PacketTypeMap;

template<>
struct PacketTypeMap<PacketID::Move_Player> {
    using type = MovePlayerPacket;
};