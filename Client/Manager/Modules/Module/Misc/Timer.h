#pragma once

#include "../Module.h"

class TimerMod : public Module {
public:
    TimerMod(Manager*);
private:
    float ticks = 30.f;
};