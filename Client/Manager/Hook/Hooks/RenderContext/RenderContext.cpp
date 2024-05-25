#include "RenderContext.h"
#include "../Actor/Tick.h"

RenderContext_Hook::RenderContext_Hook(Manager* mgr) : Hook<void, void*, void*>(mgr, "MinecraftUIRenderCtx", mgr->getSig<void*>("MinecraftUIRenderCtx"),
    [&](void* p1, void* ctx) -> void {
        
        auto instance = *(ClientInstance**)((uintptr_t)(ctx) + 0x8);
        auto lp = instance ? instance->getLocalPlayer() : nullptr;

        {
            std::lock_guard<std::mutex> lock(entityMapMutex);
            auto& entityMap = this->mgr->entityMap;
            
            for(auto iter = entityMap.begin(); iter != entityMap.end();) {
                auto [ runtimeId, entity ] = *iter;
                if(!entity || !entity->isAlive()) {
                    iter = entityMap.erase(iter);
                    Debugger::log("!");
                } else {
                    ++iter;
                };
            };
        };

        return this->_Func(p1, ctx);

    }
) {};