#pragma once

#include "ItemStack/ItemStack.h"

class Container {
private:
    virtual ~Container(void);
public:
    auto getItem(int slot) -> ItemStack* {
        return Mem::callVFunc<5, ItemStack*, int>(this, slot);
    };
};