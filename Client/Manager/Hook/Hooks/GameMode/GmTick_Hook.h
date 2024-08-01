#pragma once

#include "../../Hook.h"

class GmTick_Hook : public Hook<void, void*> {
public:
    GmTick_Hook(Manager*);
};