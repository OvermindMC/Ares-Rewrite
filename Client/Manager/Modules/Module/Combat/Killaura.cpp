#include "Killaura.h"

Killaura::Killaura(Manager* mgr) : Module(mgr, CategoryType::COMBAT, "Killaura", "Automatically attack nearby entities") {

    this->registerSetting<float>("Range", &this->range, 0.f, 12.f);
    this->registerSetting<float>("Delay", &this->range, 0.f, 1000.f);
    this->registerSetting<bool>("Multi", &this->multi);

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
                    auto entRuntimeId = entity->getRuntimeID();

                    if(!entity->isAlive() || entRuntimeId == runtimeId)
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

                closest.resize(4);

                auto i = 0;
                for(auto& [ dist, tEntity ] : closest) {
                    if(!tEntity || !tEntity->isAlive())
                        continue;
                    
                    lp->swing();
                    gm->attack(tEntity);
                    
                    if(!multi || i >= 2)
                        break;
                    
                    i++;
                };
            }
        )
    );

};