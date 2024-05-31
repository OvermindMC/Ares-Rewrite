#pragma once

#include "../Mem/Mem.h"
#include "../Utils/Utils.h"

#include "Classes/ClientInstance.h"

class MC {
public:
    static auto getClientInstance(void) -> ClientInstance*;
    static auto getEntities(void) -> std::vector<Actor*>;
};

class EntityUtils {
public:
    static auto isHostile(unsigned char) -> bool;
    static auto isPassive(unsigned char) -> bool;
};