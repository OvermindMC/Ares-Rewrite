#pragma once

#include "../../Hook.h"

static std::mutex entityMapMutex;

class Actor_TickHook : public Hook<void, Actor*> {
public:
    Actor_TickHook(Manager*);
};