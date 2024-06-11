#include "AirJump.h"

AirJump::AirJump(Manager* mgr) : Module(mgr, CategoryType::MOVE, "AirJump", "Jump in mid-air") {

    this->registerEvent<EventType::Level_Tick, EventDispatcher::EventPriority::Medium>(
        std::function<void(Level*)>(
            [&](Level* level) -> void {
                if(!this->getState())
                    return;
                
                auto instance = MC::getClientInstance();
                auto lp = instance ? instance->getLocalPlayer() : nullptr;

                if(!lp)
                    return;
                
                Module* bhop = [&]{ for (auto category : this->mgr->getCategories()) for (auto module : category->getModules()) if (module->name == "BHop") return module; return static_cast<Module*>(nullptr); }();

                if(!bhop || !bhop->getState()) {
                    auto storage = lp->getComponent<FlagComponent<OnGroundFlag>>();
                    auto entCtx = lp->getEntityCtx();

                    if(storage && !storage->contains(entCtx->entityId))
                        storage->emplace(entCtx->entityId);
                };
            }
        )
    );

};