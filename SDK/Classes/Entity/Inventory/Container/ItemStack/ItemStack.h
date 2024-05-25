#pragma once

#include "Item/Item.h"

enum EnchantmentType : int {
    Protection = 0,
    FireProtection = 1,
    FeatherFalling = 2,
    BlastProtection = 3,
    ProjectileProtection = 4,
    Thorns = 5,
    Respiration = 6,
    DepthStrider = 7,
    AquaAffinity = 8,
    Sharpness = 9,
    Smite = 10,
    BaneOfArthropods = 11,
    Knockback = 12,
    FireAspect = 13,
    Looting = 14,
    Efficiency = 15,
    SilkTouch = 16,
    Unbreaking = 17,
    Fortune = 18,
    Power = 19,
    Punch = 20,
    Flame = 21,
    Infinity = 22,
    LuckOfTheSea = 23,
    Lure = 24,
    FrostWalker = 25,
    Mending = 26,
    BindingCurse = 27,
    VanishingCurse = 28,
    Impaling = 29,
    Riptide = 30,
    Loyalty = 31,
    Channeling = 32,
    Multishot = 33,
    Piercing = 34,
    QuickCharge = 35,
    SoulSpeed = 36,
    SwiftSneak = 37
};

class ItemStack {
public:
    auto getItem(void) -> Item* {
        return this->stackCount > 0 ? **(Item***)((uintptr_t)(this) + 0x8) : nullptr;
    };

    auto isBlock(void) -> bool {
        return this ? *(uintptr_t**)((uintptr_t)(this) + 0x18) != nullptr : false;
    };
public:
    auto getEnchantValue(EnchantmentType type) -> __int16 {
        using GetEnchantValue = __int16 (__fastcall*)(EnchantmentType, ItemStack*);
        static auto _GetEnchantValue = (GetEnchantValue)Mem::findSig("48 89 5C 24 08 48 89 74 24 10 57 48 83 EC 70 48 8B F2 0F B6 D9 33 FF 48 8B CA E8 ? ? ? ?")->get(Signature::SearchType::Default);

        return (_GetEnchantValue ? _GetEnchantValue(type, this) : 0);
    };

    auto getEnchantsValue(std::vector<EnchantmentType> types) -> __int16 {
        __int16 value = 0;
        for(auto type : types) { value += this->getEnchantValue(type); };

        return value;
    };

    auto hasEnchants(void) -> bool {
        for(auto i = 0; i < 37; i++) {
            auto value = this->getEnchantValue(static_cast<EnchantmentType>(i));
            if(value > 0)
                return true;
        };
        return false;
    };
public:
    BUILD_ACCESS(unsigned char, stackCount, 0x22);
    AS_FIELD(Item*, item, getItem);
};