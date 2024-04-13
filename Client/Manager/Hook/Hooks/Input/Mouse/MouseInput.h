#pragma once

#include "../../../Hook.h"

class MouseInput_Hook : public Hook<void, void*, char, bool, short, short, short, short, bool> {
public:
    MouseInput_Hook(Manager*);
};