#pragma once

#include "../Module.h"

class Hitbox : public Module {
public:
    Hitbox(Manager*);
public:
    Vec2<float> radius = Vec2<float>(0.6f, 1.8f);
    std::map<uint8_t, Vec2<float>> cached;
};