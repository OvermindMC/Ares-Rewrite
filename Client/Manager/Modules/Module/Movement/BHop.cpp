#include "BHop.h"

BHop::BHop(Manager* mgr) : Module(mgr, CategoryType::MOVE, "Bunny-Hop", "Move like a bunny") {

    this->registerEvent<EventType::Level_Tick, EventDispatcher::EventPriority::Medium>(
        std::function<void(Level*)>(
            [&](Level* level) -> void {
                if(!this->getState())
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

                auto keys = std::vector<std::string>{ "key.forward", "key.left", "key.right", "key.back", "key.space" };
                for(auto name : keys) {
                    if(this->mgr->isUsingMCKey(name)) {
                        if(isOnGround() && !isJumping())
                            jumpFromGround();
                        break;
                    };
                };
            }
        )
    );

};