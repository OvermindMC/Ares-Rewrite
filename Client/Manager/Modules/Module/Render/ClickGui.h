#pragma once

#include "../Module.h"

class ClickGui : public Module {
public:
    ClickGui(Manager*);
public:
    float uiScale = 0.f;
};