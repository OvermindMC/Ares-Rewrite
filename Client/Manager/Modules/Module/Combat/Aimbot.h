#pragma once

#include "../Module.h"

class Aimbot : public Module {
public:
    Aimbot(Category*);

    float distance = 7.f;
};