#include "Level_Hook.h"

Level_Hook::Level_Hook(Manager* mgr) : Hook<void, Level*>(mgr, "Level_Hook", mgr->getSig<void**>("Level_VTable")[99],
    [&](Level* level) -> void {
        this->mgr->dispatchEvent<EventType::OnLevel>(level);
        return this->_Func(level);
    }
){};