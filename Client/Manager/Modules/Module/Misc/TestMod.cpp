#include "TestMod.h"

TestMod::TestMod(Manager* mgr) : Module(mgr, CategoryType::MISC, "Test Module", "For Developers") {

    this->setState(true);

    this->getEventDispatcher()->registerEvent(
        EventType::Module_Tick, EventDispatcher::EventPriority::Low, std::function<void(void)>(
            [&]() -> void {
                
                /*static int c = 0;
                c++;

                if(c > 1000)
                    this->setState(false);*/

            }
        )
    );

    this->getEventDispatcher()->registerEvent(
        EventType::Module_Toggle, EventDispatcher::EventPriority::Low, std::function<void(void)>(
            [&]() -> void {
                if(!this->getState()) {
                    Debugger::log("Goodbye...");
                    this->client->stop();
                };
            }
        )
    );

    this->getEventDispatcher()->registerEvent(
        EventType::Level_Tick, EventDispatcher::EventPriority::Highest, std::function<void(Level*)>(
            [&](Level* level) -> void {
                Debugger::log("!");
            }
        )
    );

    this->getEventDispatcher()->registerEvent(
        EventType::Level_Tick, EventDispatcher::EventPriority::Highest, std::function<void(Level*)>(
            [&](Level* level) -> void {
                
                auto instance = MC::getClientInstance();
                auto lp = instance->getLocalPlayer();

                if(lp) {

                    auto myPos = lp->getPos();
                    auto myRuntimeId = lp->getRuntimeID();
                    auto& entityMap = this->mgr->entityMap;
                    auto targets = std::vector<std::pair<uint64_t, double>>();

                    for(const auto& [ runtimeId, entity ] : entityMap) {

                        if(runtimeId == myRuntimeId)
                            continue;
                        
                        auto dist = entity->getPos().dist(myPos);

                        if(dist <= 12.f)
                            targets.push_back(std::pair<uint64_t, double>(runtimeId, dist));

                    };

                    std::sort(targets.begin(), targets.end(), [&](const std::pair<uint64_t, double>& a, const std::pair<uint64_t, double>& b) {
                        return a.second < b.second;
                    });

                    if(targets.empty())
                        return;
                    
                    auto [ tRuntimeId, tDist ] = targets.front();
                    auto target = entityMap.contains(tRuntimeId) ? entityMap.at(tRuntimeId) : nullptr;

                    if(target) {

                        auto gm = lp->getGameMode();
                        
                        lp->swing();
                        gm->attack(target);

                    };

                };

            }
        )
    );

};