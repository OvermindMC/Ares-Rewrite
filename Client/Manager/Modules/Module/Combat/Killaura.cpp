#include "Killaura.h"

Killaura::Killaura(Category* c) : Module(c, "Killaura") {
    this->registerEvent<EventType::OnLevel, Level*>(
        EventDispatcher::EventPriority::High,
        [&](Level* level) {
            if(!this->isEnabled())
                return;
            
            ClientInstance* ci = MC::getClientInstance();
            std::string screenName = ci ? ci->getTopScreenName() : "";

            if(screenName.rfind("hud_screen") == std::string::npos)
                return;
            
            auto now = std::chrono::high_resolution_clock::now();
            if(timepoint > now)
                return;
            
            timepoint += std::chrono::milliseconds(this->msDelay);
            
            Player* player = MC::getLocalPlayer();
            GameMode* GM = player->getGameMode();

            if(!player || !GM)
                return;
            
            uint64_t lRuntimeId = player->getRuntimeId();
            Vec3 myPos = player->getPosition();

            auto entities = MC::getEntities();
            if(entities.size() <= 1)
                return;
            
            std::sort(entities.begin(), entities.end(), [&](Actor* a, Actor* b) {
                return a->getPosition().distance(myPos) < b->getPosition().distance(myPos);
            });

            int i = 0;
            for(auto ent : entities) {
                if(ent->getRuntimeId() == lRuntimeId || !ent->isAlive())
                    continue;
                
                Vec3 tPos = ent->getPosition();

                if(tPos.distance(myPos) > this->distance)
                    break;

                i++;
                player->swing();
                GM->attack(ent);
                
                if(!multi || i >= this->attacksPerTick)
                    break;
            }
        }
    );
};