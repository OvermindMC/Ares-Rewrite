#pragma once

#include "../Module.h"

class ClickGui : public Module {
public:
    ClickGui(Manager*);
public:
    auto reachOff(float* x, float xOff, float modifier) -> void;
public:
    float uiScale = 0.f;
public:
    class ClickGuiWindow* dragWin = nullptr;
    Vec2<float> dragStart;
public:
    std::string dragSlider;
    bool isDraggingSlider = false;
};