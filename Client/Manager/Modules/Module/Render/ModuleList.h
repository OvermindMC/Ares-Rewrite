#pragma once

#include "../Module.h"

class ModuleList : public Module {
public:
    ModuleList(Manager*);

    auto reachOff(float* x, float xOff, float modifier) -> void;

    float fontSize = 18.f;
    float uiScale = 0.f;

    ImVec2 pad = ImVec2(
        6.f, 0.f
    );
};