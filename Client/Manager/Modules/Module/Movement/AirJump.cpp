#include "AirJump.h"

AirJump::AirJump(Manager* mgr) : Module(mgr, CategoryType::MOVE, "AirJump", "Jump in mid-air") {

    static auto bhop = (Module*)nullptr;

    this->registerEvent<EventType::Modules_Initialized, EventDispatcher::EventPriority::Low>(
        std::function<void(void)>(
            [&](void) -> void {
                bhop = [&]{ for (auto category : this->mgr->getCategories()) for (auto module : category->getModules()) if (module->name == "Bunny-Hop") return module; return static_cast<Module*>(nullptr); }();
            }
        )
    );
    
    this->registerEvent<EventType::Level_Tick, EventDispatcher::EventPriority::Medium>(
        std::function<void(Level*)>(
            [&](Level* level) -> void {
                if(!this->getState())
                    return;
                
                auto instance = MC::getClientInstance();
                auto lp = instance ? instance->getLocalPlayer() : nullptr;

                if(!lp)
                    return;
                
                auto storage = lp->getComponent<FlagComponent<OnGroundFlag>>();
                auto entCtx = lp->getEntityCtx();
                
                if(!bhop || !bhop->getState()) {
                    if(storage && !storage->contains(entCtx->entityId))
                        storage->emplace(entCtx->entityId);
                };
            }
        )
    );

    this->registerEvent<EventType::KeyInput, EventDispatcher::EventPriority::Medium>(
        std::function<void(uint64_t, bool, bool*)>{
            [&](uint64_t key, bool isDown, bool* cancel) -> void {
                if(!this->getState() || !isDown)
                    return;
                
                auto instance = MC::getClientInstance();
                auto lp = instance ? instance->getLocalPlayer() : nullptr;
                auto screenName = instance ? instance->getScreenName() : "";

                if(!lp || screenName.rfind("hud_screen") == std::string::npos)
                    return;
                
                auto isOnGround = [&](void) -> bool {
                    auto storage = lp->getComponent<FlagComponent<OnGroundFlag>>();
                    auto entCtx = lp->getEntityCtx();

                    return storage ? storage->contains(entCtx->entityId) : false;
                };

                auto isJumping = [&](void) -> bool {
                    auto storage = lp->getComponent<FlagComponent<JumpFromGroundRequestFlag>>();
                    auto entCtx = lp->getEntityCtx();

                    return storage ? storage->contains(entCtx->entityId) : false;
                };

                auto jumpFromGround = [&](void) -> void {
                    auto storage = lp->getComponent<FlagComponent<JumpFromGroundRequestFlag>>();
                    auto entCtx = lp->getEntityCtx();

                    if(storage && !storage->contains(entCtx->entityId))
                        storage->emplace(entCtx->entityId);
                };
                
                if(key == this->mgr->getMcKey("key.jump")) {
                    jumpFromGround();
                };
            }
        }
    );

};