#include "GmTick_Hook.h"

GmTick_Hook::GmTick_Hook(Manager* mgr) : Hook<void, void*, void*, void*>(mgr, "GmTick_Hook", mgr->getSig<void**>("GameMode_VTable")[8],
    [&](void* GM, void* p2, void* p3) -> void {
        
        //

        return this->_Func(GM, p2, p3);
    }
){};