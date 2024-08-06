#include "LookInp_Hook.h"

LookInp_Hook::LookInp_Hook(Manager* mgr) : Hook<void, EntityContext&, void*, Vec2&>(mgr, "HandleLookInput_Func", mgr->getSig<void*>("HandleLookInput_Func"),
    [&](EntityContext& ctx, void* p2, Vec2& lookDir) -> void {
        this->mgr->dispatchEvent<EventType::OnFirstPersonLook>(&lookDir);
        return this->_Func(ctx, p2, lookDir);
    }
){};