#include "Killaura.h"

Killaura::Killaura(Manager* mgr) : Module(mgr, CategoryType::COMBAT, "Killaura", "Automatically attack nearby entities") {

    this->registerEvent<EventType::Level_Tick, EventDispatcher::EventPriority::Highest>(
        std::function<void(Level*)>(
            [&](Level* level) -> void {
                if(!this->getState())
                    return;
                
                auto instance = MC::getClientInstance();
                auto lp = instance ? instance->getLocalPlayer() : nullptr;

                if(!lp)
                    return;
                
                auto& entityMap = this->mgr->entityMap;
                auto runtimeId = lp->getRuntimeID();
                auto gm = lp->getGameMode();
                auto myPos = lp->getPos();

                if(!gm || entityMap.empty())
                    return;
                
                auto closest = std::vector<std::pair<double, Actor*>>();
                for(auto [ entRuntimeId, ent ] : entityMap) {
                    if(entRuntimeId == runtimeId)
                        continue;
                    
                    auto dist = myPos.dist(ent->getPos());
                    
                    if(dist <= 12.f)
                        closest.push_back(std::pair<double, Actor*>(dist, ent));
                };

                if(closest.empty())
                    return;

                std::sort(closest.begin(), closest.end(), [&](std::pair<double, Actor*> a, std::pair<double, Actor*> b) {
                    return a.first < b.first;
                });

                auto first = closest.front();
                
                lp->swing();
                gm->attack(first.second);
            }
        )
    );

};