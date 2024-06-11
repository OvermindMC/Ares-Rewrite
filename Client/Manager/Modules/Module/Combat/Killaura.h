#pragma once

#include "../Module.h"

class Killaura : public Module {
public:
    Killaura(Manager*);
private:
    float range = 12.f;

    bool multi = true;
    bool rotations = true;
    
    std::chrono::steady_clock::time_point timepoint = std::chrono::high_resolution_clock::now();
    int msDelay = 120;
    int attacksPerTick = 3;
};