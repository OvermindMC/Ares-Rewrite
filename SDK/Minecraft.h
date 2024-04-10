#pragma once

#include "../Mem/Mem.h"
#include "../Utils/Utils.h"

#include "Classes/ClientInstance.h"

class MC {
public:
    static auto getClientInstance(void) -> ClientInstance*;
};

class EntityUtils {
public:
    static auto isHostile(unsigned char) -> bool;
    static auto isPassive(unsigned char) -> bool;
};