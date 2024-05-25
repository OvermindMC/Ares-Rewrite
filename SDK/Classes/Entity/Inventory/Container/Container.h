#pragma once

#include "ItemStack/ItemStack.h"

class Container {
public:
    auto getItem(int slot) -> ItemStack* {
        return Mem::callVFunc<5, ItemStack*, int>(this, slot);
    };

    auto getSlots(void) -> std::vector<ItemStack*> {
        auto list = std::vector<ItemStack*>();

        for(auto i = 0; i < this->getSize(); i++) {
            list.push_back(this->getItem(i));
        };

        return list;
    };
public:
    auto getSize(void) -> size_t {
        return Mem::callVFunc<17, size_t>(this);
    };
};