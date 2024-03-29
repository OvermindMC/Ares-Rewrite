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
    virtual auto outOfWorld(void) -> void;
    virtual auto reloadHardcoded(enum ActorInitializationMethod, class VariantParameterList const &) -> void;
    virtual auto reloadHardcodedClient(enum ActorInitializationMethod, class VariantParameterList const &) -> void;
    virtual auto initializeComponents(enum ActorInitializationMethod, class VariantParameterList const &) -> void;
    virtual auto reloadComponents(enum ActorInitializationMethod, class VariantParameterList const &) -> void;
    virtual auto _serverInitItemStackIds(void) -> void;
    virtual auto _doInitialMove(void) -> void;
    virtual auto resetUserPos(bool) -> void;
    virtual auto getOwnerEntityType(void) -> unsigned long long;
    virtual auto remove(void) -> void;
    virtual auto isRuntimePredictedMovementEnabled(void) -> bool;
    virtual auto getFiringPos(void) -> Vec3<float>;
    virtual auto getInterpolatedBodyRot(float) -> float;
    virtual auto getInterpolatedHeadRot(float) -> float;
    virtual auto getInterpolatedBodyYaw(float) -> float;
    virtual auto getYawSpeedInDegreesPerSecond(void) -> float;
    virtual auto getInterpolatedRidingOffset(float, int) -> Vec3<float>;
    virtual auto resetInterpolated(void) -> void;
    virtual auto isFireImmune(void) -> bool;
    virtual auto blockedByShield(struct ActorDamageSource*, Actor*) -> void;
    virtual auto canDisableShield(void) -> bool;
    virtual auto teleportTo(Vec3<float>*, bool, int, int, bool) -> void;
    virtual auto lerpMotion(Vec3<float>*) -> void;
    virtual auto tryCreateAddActorPacket(void) -> unsigned long long;
    virtual auto normalTick(void) -> void;
    virtual auto baseTick(void) -> void;
    virtual auto passengerTick(void) -> void;
    virtual auto startRiding(Actor*) -> bool;
    virtual auto addPassenger(Actor*) -> void;
    virtual auto getExitTip(std::string const &, enum InputMode, enum NewInteractionModel) -> std::basic_string<char, struct std::char_traits<char>, class std::allocator<char>>;
    virtual auto getEntityLocNameString(void) -> std::basic_string<char, struct std::char_traits<char>, class std::allocator<char>>;
    virtual auto isInWall(void) -> bool;
    virtual auto isInvisible(void) -> bool;
    virtual auto canShowNameTag(void) -> bool;
    virtual auto getFormattedNameTag(void) -> std::basic_string<char, struct std::char_traits<char>, class std::allocator<char>>;
    virtual auto getNameTagTextColor(void) -> unsigned long long;
    virtual auto getShadowRadius(void) -> float;
    virtual auto getHeadLookVector(float) -> Vec3<float>;
    virtual auto canInteractWithOtherEntitiesInGame(void) -> bool;
    virtual auto getBrightness(float, struct IConstBlockSource*) -> float;
    virtual auto playerTouch(class Player*) -> void;
    virtual auto isImmobile(void) -> bool;
    virtual auto isSilentObserver(void) -> bool;
    virtual auto isPickable(void) -> bool;
    virtual auto isSleeping(void) -> bool;
    virtual auto setSleeping(bool) -> void;
    virtual auto setSneaking(bool) -> void;
    virtual auto isBlocking(void) -> bool;
    virtual auto isDamageBlocked(struct ActorDamageSource*) -> bool;
    virtual auto isAlive(void) -> bool;
    virtual auto isOnFire(void) -> bool;
    virtual auto isSurfaceMob(void) -> bool;
    virtual auto isTargetable(void) -> bool;
    virtual auto isLocalPlayer(void) -> bool;
    virtual auto isPlayer(void) -> bool;
    virtual auto canAttack(Actor*, bool) -> bool;
    virtual auto setTarget(Actor*) -> bool;
    virtual auto isValidTarget(Actor*) -> bool;
    virtual auto attack(Actor*, enum ActorDamageCause*) -> bool;
    virtual auto performRangedAttack(Actor*, float) -> void;
    virtual auto setOwner(uint64_t) -> void;
    virtual auto setSitting(bool) -> void;
    virtual auto onTame(void) -> void;
    virtual auto onFailedTame(void) -> void;
    virtual auto setStanding(bool) -> void;
    virtual auto canPowerJump(void) -> bool;
    virtual auto isEnchanted(void) -> bool;
    virtual auto shouldRender(void) -> bool;
    virtual auto playAmbientSound(void) -> void;
    virtual auto getAmbientSound(void) -> enum LevelSoundEvent;
    virtual auto isInvulnerableTo(class ActorDamageSource*) -> bool;
    virtual auto getBlockDamageCause(class Block&) -> enum ActorDamageCause;
    virtual auto doFireHurt(int) -> void;
    virtual auto onLightningHit(void) -> void;
    virtual auto feed(int) -> void;
    virtual auto handleEntityEvent(enum ActorEvent, int) -> void;
    virtual auto getPickRadius(void) -> float;
    virtual auto getActorRendererId(void) -> class HashedStruct*;
    virtual auto despawn(void) -> void;
    virtual auto setArmor(enum ArmorSlot, class ItemStack*) -> void;
    virtual auto getArmorMaterialTypeInSlot(enum ArmorSlot) -> enum ArmorMaterialType;
    virtual auto getArmorMaterialTextureTypeInSlot(enum ArmorSlot) -> enum ArmorTextureType;
    virtual auto getArmorColorInSlot(enum ArmorSlot, int) -> float;
    virtual auto setEquippedSlot(enum EquipmentSlot, class ItemStack const&) -> void;
    virtual auto setCarriedItem(class ItemStack*) -> void;
    virtual auto getCarriedItem(void) -> class ItemStack*;
    virtual auto setOffhandSlot(class ItemStack*) -> void;
    virtual auto getEquippedTotem(void) -> class ItemStack*;
    virtual auto consumeTotem(void) -> void;
    virtual auto save(class CompoundTag*) -> bool;
    virtual auto load(class CompoundTag*, class DataLoadHelper*) -> bool;
    virtual auto queryEntityRenderer(void) -> void*;
    virtual auto getSourceUniqueID(void) -> uint64_t;
    virtual auto canFreeze(void) -> bool;
    virtual auto getLiquidAABB(enum MaterialType) -> AABB<float>;
    virtual auto handleInsidePortal(Vec3<int>*) -> void;
};