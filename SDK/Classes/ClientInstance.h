#pragma once

#include "Entity/Player.h"

class ClientInstance {
public:
    auto getLocalPlayer(void) -> Player*;
public:
    BUILD_ACCESS(Vec2<float>, mousePos, 0x498);
};