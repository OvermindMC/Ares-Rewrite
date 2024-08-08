#pragma once

#include "../../Hook.h"

class KeyInput_Hook : public Hook<void, uint64_t, bool> {
public:
    KeyInput_Hook(Manager*);
};