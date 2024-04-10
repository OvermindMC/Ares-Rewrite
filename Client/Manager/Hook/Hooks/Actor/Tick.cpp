#include "Tick.h"

Actor_TickHook::Actor_TickHook(Manager* mgr) : Hook<void, Actor*>(mgr, "Actor_Tick", (void*)mgr->getSig<uintptr_t**>("Actor_VTable")[29],
    [&](Actor* entity) -> void {
        
        //auto runtimeId = entity->getRuntimeID();
        //
        
        return this->_Func(entity);
    }
) {};