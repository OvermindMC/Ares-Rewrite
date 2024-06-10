#pragma once

#include "../Module.h"

class Hitbox : public Module {
public:
    Hitbox(Manager*);
public:
    Vec2<float> radius;
    std::map<uint8_t, Vec2<float>> cached;
};