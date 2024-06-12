#pragma once

#include "../Module.h"

class Speed : public Module {
public:
    Speed(Manager*);

    float speed = .53f;

    int msDelay = 10;
    std::chrono::steady_clock::time_point timepoint = std::chrono::high_resolution_clock::now();
};