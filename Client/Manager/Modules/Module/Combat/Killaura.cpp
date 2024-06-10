#include "Killaura.h"

Killaura::Killaura(Manager* mgr) : Module(mgr, CategoryType::COMBAT, "Killaura", "Automatically attack nearby entities") {

    this->registerSetting("Range", &this->range, 0.f, 12.f);
    this->registerSetting("Delay", &this->msDelay, 0, 1000);
    this->registerSetting("Hits Per Tick", &this->attacksPerTick, 1, 6, &this->multi);
    this->registerSetting("Multi", &this->multi);

    this->registerEvent<EventType::Level_Tick, EventDispatcher::EventPriority::Highest>(
        std::function<void(Level*)>(
            [&](Level* level) -> void {
                if(!this->getState())
                    return;
                
                auto now = std::chrono::high_resolution_clock::now();
                if(timepoint > now)
                    return;
                
                timepoint += std::chrono::milliseconds(this->msDelay);
                
                auto instance = MC::getClientInstance();
                auto lp = instance ? instance->getLocalPlayer() : nullptr;

                if(!lp)
                    return;
                
                auto entities = MC::getEntities();
                auto runtimeId = lp->getRuntimeID();
                auto gm = lp->getGameMode();
                auto myPos = lp->getPos();

                auto closest = std::vector<std::pair<double, Actor*>>();
                for(auto entity : entities) {
                    if(!entity || !entity->isAlive())
                        continue;
                    
                    auto typeId = entity->getEntityTypeId();

                    if(typeId != 63 && !EntityUtils::isHostile(typeId) && !EntityUtils::isPassive(typeId))
                        continue;
                    
                    if(entity->getRuntimeID() == runtimeId)
                        continue;
                    
                    auto dist = myPos.dist(entity->getPos());

                    if(dist <= range)
                        closest.push_back(std::pair<double, Actor*>(dist, entity));
                };

                if(closest.empty())
                    return;

                std::sort(closest.begin(), closest.end(), [&](std::pair<double, Actor*> a, std::pair<double, Actor*> b) {
                    return a.first < b.first;
                });

                auto i = 0;
                for(auto [ dist, tEntity ] : closest) {
                    if(!tEntity || !tEntity->isAlive())
                        continue;
                    
                    i++;
                    lp->swing();
                    gm->attack(tEntity);
                    
                    if(!multi || i >= this->attacksPerTick)
                        break;
                };
            }
        )
    );

};