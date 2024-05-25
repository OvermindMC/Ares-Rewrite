#include "Tick.h"
#include "../Tick.h"

Level_TickHook::Level_TickHook(Manager* mgr) : Hook<void, Level*>(mgr, "Level_Tick", mgr->getSig<void**>("Level_VTable")[99],
    [&](Level* level) -> void {
        
        this->mgr->dispatchEvent<EventType::Level_Tick, Level*>(level);
        return this->_Func(level);

    }
) {};