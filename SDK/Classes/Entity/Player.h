#pragma once

#include "Actor.h"

class Player : public Actor {
private:
    virtual ~Player(void);
public:
    virtual auto knockback(class Actor*, int, float, float, float, float, float) -> void;
    virtual auto spawnAnim(void) -> void;
    virtual auto setSprinting(bool) -> void;
    virtual auto getHurtSound(void) -> enum LevelSoundEvent;
    virtual auto getDeathSound(void) -> enum LevelSoundEvent;
    virtual auto getSpeed(void) -> float;
    virtual auto setSpeed(float) -> void;
    virtual auto hurtEffects(class ActorDamageSource*, float, bool, bool) -> void;
    virtual auto aiStep(void) -> void;
    virtual auto pushActors(void) -> void;
    virtual auto checkSpawnRules(bool) -> bool;
    virtual auto checkSpawnObstruction(void) -> bool;
    virtual auto getItemUseDuration(void) -> __int64;
    virtual auto getItemUseStartupProgress(void) -> float;
    virtual auto getItemUseIntervalProgress(void) -> float;
    virtual auto getMaxHeadXRot(void) -> float;
    virtual auto isAlliedTo(class Mob*) -> bool;
    virtual auto doHurtTarget(class Actor*, enum ActorDamageCause*) -> bool;
    virtual auto getArmorValue(void) -> __int64;
    virtual auto hurtArmorSlots(class ActorDamageSource const&, int, std::bitset<4>) -> void;
    virtual auto setDamagedArmor(enum ArmorSlot, class ItemStack*) -> void;
    virtual auto sendArmorDamage(std::bitset<4>) -> void;
    virtual auto sendArmor(std::bitset<4>) -> void;
    virtual auto getAllHand(void) -> __int64;
    virtual auto getAllEquipment(void) -> __int64;
    virtual auto dropEquipmentOnDeath(void) -> __int64;
    virtual auto dropEquipmentOnDeath(class ActorDamageSource*, int) -> void;
    virtual auto clearVanishEnchantedItemsOnDeath(void) -> void;
    virtual auto sendInventory(bool) -> void;
    virtual auto getDamageAfterEnchantReduction(class ActorDamageSource*, float) -> float;
    virtual auto createAIGoals(void) -> bool;
    virtual auto onBorn(Actor*, Actor*) -> void;
    virtual auto setItemSlot(enum EquipmentSlot, class ItemStack*) -> bool;
    virtual auto setTransitioningSitting(bool) -> void;
};