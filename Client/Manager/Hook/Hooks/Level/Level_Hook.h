#pragma once

#include "../../Hook.h"

class Level_Hook : public Hook<void, Level*> {
public:
    Level_Hook(Manager* mgr);
};