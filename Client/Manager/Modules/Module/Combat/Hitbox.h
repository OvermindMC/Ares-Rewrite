#pragma once

#include "../Module.h"

class Hitbox : public Module {
public:
    Hitbox(Category*);

    Vec2 radius = { 2.f, 2.f };
    std::map<uint8_t, Vec2> cached;
};