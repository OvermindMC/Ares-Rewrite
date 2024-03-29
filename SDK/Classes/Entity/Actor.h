#pragma once

#include "EntityContext.h"
#include "Component/Component.h"

class Actor {
public:
    auto getEntityCtx(void) -> EntityContext*;
public:
    template<typename T>
    auto getComponent(void) -> entt::basic_storage<T, EntityId>* {
        static auto sig = Mem::findSig("E8 ? ? ? ? BA 70 27 BA F0")->get(Signature::SearchType::Ref);

        if (!sig)
            return nullptr;

        using AssureT = entt::basic_storage<T, EntityId>* (__fastcall*)(entt::basic_registry<EntityId>&, entt::id_type);
        auto assureF = (AssureT)(sig);

        auto type = entt::type_id<T>();
        auto ctx = this->getEntityCtx();

        return assureF(ctx->registry, type.hash());
    };
public:
    auto getRuntimeID(void) -> unsigned long long;
private:
    virtual ~Actor(void);
public:
    virtual auto getStatusFlag(enum ActorFlags) -> bool;
    virtual auto setStatusFlag(enum ActorFlags, bool) -> void;
public:
    virtual auto outOfWorld(void) -> void;
public:
    virtual auto reloadHardcoded(enum ActorInitializationMethod, class VariantParameterList const &) -> void;
    virtual auto reloadHardcodedClient(enum ActorInitializationMethod, class VariantParameterList const &) -> void;
    virtual auto initializeComponents(enum ActorInitializationMethod, class VariantParameterList const &) -> void;
    virtual auto reloadComponents(enum ActorInitializationMethod, class VariantParameterList const &) -> void;
public:
    virtual auto _serverInitItemStackIds(void) -> void;
    virtual auto _doInitialMove(void) -> void;
    virtual auto resetUserPos(bool) -> void;
public:
    virtual auto getOwnerEntityType(void) -> unsigned long long;
    virtual auto remove(void) -> void;
public:
    virtual auto isRuntimePredictedMovementEnabled(void) -> bool;
public:
    virtual auto getFiringPos(void) -> Vec3<float>;
    virtual auto getInterpolatedBodyRot(float) -> float;
    virtual auto getInterpolatedHeadRot(float) -> float;
    virtual auto getInterpolatedBodyYaw(float) -> float;
    virtual auto getYawSpeedInDegreesPerSecond(void) -> float;
    virtual auto getInterpolatedRidingOffset(float, int) -> Vec3<float>;
    virtual auto resetInterpolated(void) -> void;
public:
    virtual auto isFireImmune(void) -> bool;
    virtual auto blockedByShield(struct ActorDamageSource*, Actor*) -> void;
    virtual auto canDisableShield(void) -> bool;
public:
    virtual auto teleportTo(Vec3<float>*, bool, int, int, bool) -> void;
    virtual auto lerpMotion(Vec3<float>*) -> void;
public:
    virtual auto tryCreateAddActorPacket(void) -> unsigned long long;
public:
    virtual auto normalTick(void) -> void;
    virtual auto baseTick(void) -> void;
    virtual auto passengerTick(void) -> void;
public:
    virtual auto startRiding(Actor*) -> bool;
    virtual auto addPassenger(Actor*) -> void;
public:
    virtual auto getExitTip(std::string const &, enum InputMode, enum NewInteractionModel) -> std::basic_string<char, struct std::char_traits<char>, class std::allocator<char>>;
    virtual auto getEntityLocNameString(void) -> std::basic_string<char, struct std::char_traits<char>, class std::allocator<char>>;
public:
    virtual auto isInWall(void) -> bool;
    virtual auto isInvisible(void) -> bool;
    virtual auto canShowNameTag(void) -> bool;
public:
    virtual auto getFormattedNameTag(void) -> std::basic_string<char, struct std::char_traits<char>, class std::allocator<char>>;
    virtual auto getNameTagTextColor(void) -> unsigned long long;
public:
    virtual auto getShadowRadius(void) -> float;
    virtual auto getHeadLookVector(float) -> Vec3<float>;
public:
    virtual auto canInteractWithOtherEntitiesInGame(void) -> bool;
public:
    virtual auto getBrightness(float, struct IConstBlockSource*) -> float;
};