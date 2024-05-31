#pragma once

#include "../Packet.h"
#include <bitset>

class PlayerAuthInputPacket : public Packet {
public:
    enum class InputData : int {
        Ascend                     = 0x0,
        Descend                    = 0x1,
        NorthJump                  = 0x2,
        JumpDown                   = 0x3,
        SprintDown                 = 0x4,
        ChangeHeight               = 0x5,
        Jumping                    = 0x6,
        AutoJumpingInWater         = 0x7,
        Sneaking                   = 0x8,
        SneakDown                  = 0x9,
        Up                         = 0xA,
        Down                       = 0xB,
        Left                       = 0xC,
        Right                      = 0xD,
        UpLeft                     = 0xE,
        UpRight                    = 0xF,
        WantUp                     = 0x10,
        WantDown                   = 0x11,
        WantDownSlow               = 0x12,
        WantUpSlow                 = 0x13,
        Sprinting                  = 0x14,
        AscendBlock                = 0x15,
        DescendBlock               = 0x16,
        SneakToggleDown            = 0x17,
        PersistSneak               = 0x18,
        StartSprinting             = 0x19,
        StopSprinting              = 0x1A,
        StartSneaking              = 0x1B,
        StopSneaking               = 0x1C,
        StartSwimming              = 0x1D,
        StopSwimming               = 0x1E,
        StartJumping               = 0x1F,
        StartGliding               = 0x20,
        StopGliding                = 0x21,
        PerformItemInteraction     = 0x22,
        PerformBlockActions        = 0x23,
        PerformItemStackRequest    = 0x24,
        HandledTeleport            = 0x25,
        Emoting                    = 0x26,
        MissedSwing                = 0x27,
        StartCrawling              = 0x28,
        StopCrawling               = 0x29,
        StartFlying                = 0x2A,
        StopFlying                 = 0x2B,
        ReceivedServerData         = 0x2C,
        InClientPredictedInVehicle = 0x2D,
        PaddlingLeft               = 0x2E,
        PaddlingRight              = 0x2F,
    };

    enum class InputMode : int {
        Undefined        = 0x0,
        Mouse            = 0x1,
        Touch            = 0x2,
        GamePad          = 0x3,
        MotionController = 0x4,
    };

    enum class ClientPlayMode : int {
        Normal              = 0x0,
        Teaser              = 0x1,
        Screen              = 0x2,
        Viewer              = 0x3,
        Reality             = 0x4,
        Placement           = 0x5,
        LivingRoom          = 0x6,
        ExitLevel           = 0x7,
        ExitLevelLivingRoom = 0x8,
        NumModes            = 0x9,
    };

    enum class NewInteractionModel : int {
        Touch     = 0x0,
        Crosshair = 0x1,
        Classic   = 0x2,
    };
public:
    Vec2<float>                                              bodyRot;
    Vec3<float>                                              position;
    float                                                    yeadYaw;
    Vec3<float>                                              posDelta;
    Vec2<float>                                              analogMoveVector;
    Vec2<float>                                              vehicleRotation;
    Vec2<float>                                              move;
    Vec3<float>                                              gazeDir;
    std::bitset<39>                                          inputData;
    InputMode                                                inputMode;
    ClientPlayMode                                           playMode;
    NewInteractionModel                                      newInteractionModel;
    uint64_t                                                 clientTick;
    std::unique_ptr<void*>                                   itemUseTransaction;
    std::unique_ptr<void*>                                   itemStackRequest;
    void*                                                    playerBlockActions;
    uint64_t                                                 predictedVehicle;
public:
    template<InputData flag>
    auto hasFlag(void) -> bool {
        return this->inputData.count() ? this->inputData.test(static_cast<size_t>(flag)) : false;
    };
};

template<PacketID>
struct PacketTypeMap;

template<>
struct PacketTypeMap<PacketID::Player_Auth_Input> {
    using type = PlayerAuthInputPacket;
};