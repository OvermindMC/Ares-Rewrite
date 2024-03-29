#pragma once

#include "Entity/Player.h"

class ClientInstance {
public:
    auto getLocalPlayer(void) -> Player*;
};