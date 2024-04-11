#pragma once

#include "../../../Hook.h"

class KeyInput_Hook : public Hook<void, unsigned long long, bool> {
public:
    KeyInput_Hook(Manager*);
};