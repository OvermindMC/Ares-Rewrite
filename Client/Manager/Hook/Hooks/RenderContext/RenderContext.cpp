#include "RenderContext.h"

RenderContext_Hook::RenderContext_Hook(Manager* mgr) : Hook<void, void*, void*>(mgr, "MinecraftUIRenderCtx", mgr->getSig<void*>("MinecraftUIRenderCtx"),
    [&](void* p1, void* ctx) -> void {
        
        auto instance = *(ClientInstance**)((uintptr_t)(ctx) + 0x8);
        auto lp = instance ? instance->getLocalPlayer() : nullptr;

        return this->_Func(p1, ctx);

    }
) {};