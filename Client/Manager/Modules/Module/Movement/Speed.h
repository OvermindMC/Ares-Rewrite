#pragma once

#include "../Module.h"

class Speed : public Module {
public:
    Speed(Manager*);

    float speed = .53f;
};