#pragma once

#include "../../Hook.h"

class ScreenController_TickHook : public Hook<void, ScreenController*> {
public:
    ScreenController_TickHook(Manager*);
};