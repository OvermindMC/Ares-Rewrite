#pragma once

#include "../Module.h"

class Killaura : public Module {
public:
    Killaura(Manager*);
private:
    float range = 12.f;
    bool multi = true;
private:
    std::chrono::steady_clock::time_point timepoint = std::chrono::high_resolution_clock::now();
    int msDelay = 50;
    int attacksPerTick = 3;
};