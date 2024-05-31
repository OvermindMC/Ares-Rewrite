#pragma once

#include "../../Hook.h"

class Level_TickHook : public Hook<void, Level*> {
public:
    Level_TickHook(Manager*);
};