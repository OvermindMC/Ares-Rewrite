#include "GmTick_Hook.h"

GmTick_Hook::GmTick_Hook(Manager* mgr) : Hook<void, GameMode*>(mgr, "GmTick_Hook", mgr->getSig<void**>("GameMode_VTable")[8],
    [&](GameMode* GM) -> void {
        this->mgr->dispatchEvent<EventType::OnGameMode>(GM);
        return this->_Func(GM);
    }
){};