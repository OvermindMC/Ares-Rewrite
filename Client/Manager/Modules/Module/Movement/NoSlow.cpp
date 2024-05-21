#include "NoSlow.h"

NoSlow::NoSlow(Manager* mgr) : Module(mgr, CategoryType::MOVE, "NoSlow", "Disable Slowdown Multipliers") {

    this->registerEvent<EventType::Level_Tick, EventDispatcher::EventPriority::Medium>(
        std::function<void(Level*)>(
            [&](Level* level) -> void {
                if(!this->getState())
                    return;
                
                auto instance = MC::getClientInstance();
                auto lp = instance ? instance->getLocalPlayer() : nullptr;

                if(!lp)
                    return;
                
                auto entCtx = lp->getEntityCtx();
                auto itemUseComp = lp->getComponent<ItemInUseComponent>();
                auto blockSlowMultis = lp->getComponent<BlockMovementSlowdownMultiplierComponent>();

                if(itemUseComp && itemUseComp->contains(entCtx->entityId))
                    itemUseComp->erase(entCtx->entityId);
                
                if(blockSlowMultis && blockSlowMultis->contains(entCtx->entityId))
                    blockSlowMultis->erase(entCtx->entityId);
            }
        )
    );

    this->registerEvent<EventType::Module_Toggle, EventDispatcher::EventPriority::Low>(
        std::function<void(void)>(
            [&](void) -> void {
                if(!this->getState()) {
                    auto instance = MC::getClientInstance();
                    auto lp = instance ? instance->getLocalPlayer() : nullptr;

                    if(!lp)
                        return;
                    
                    auto entCtx = lp->getEntityCtx();
                    auto blockSlowMultis = lp->getComponent<BlockMovementSlowdownMultiplierComponent>();

                    if(blockSlowMultis && !blockSlowMultis->contains(entCtx->entityId))
                        blockSlowMultis->emplace(entCtx->entityId);
                }
            }
        )
    );

};