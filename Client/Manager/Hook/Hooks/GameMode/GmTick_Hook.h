#pragma once

#include "../../Hook.h"

class GmTick_Hook : public Hook<void, GameMode*> {
public:
    GmTick_Hook(Manager*);
};