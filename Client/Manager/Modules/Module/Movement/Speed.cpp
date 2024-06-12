#include "Speed.h"

Speed::Speed(Manager* mgr) : Module(mgr, CategoryType::MOVE, "Speed", "Enhance movement speed") {

    this->registerSetting("Speed", &this->speed, 0.5f, 3.f);
    this->registerSetting("Delay", &this->msDelay, 0, 1000);

    this->registerEvent<EventType::Level_Tick, EventDispatcher::EventPriority::Medium>(
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
                auto screenName = instance ? instance->getScreenName() : "";
                
                if(!lp || screenName.rfind("hud_screen") == std::string::npos)
                    return;
                
                static auto keys = std::vector<std::pair<std::string, bool>>{ {"key.forward", false}, {"key.left", false}, {"key.right", false}, {"key.back", false} };
                for(auto& data : keys) {
                    data.second = this->mgr->isUsingMCKey(data.first);
                };

                auto it = std::find_if(keys.begin(), keys.end(), [&](const std::pair<std::string, bool>& data){
                    return data.second == true;
                });

                if(it == keys.end())
                    return;
                
                auto stateVec = lp->getComponentData<StateVectorComponent>();
                auto rotVec = lp->getComponentData<ActorRotationComponent>();

                if(!stateVec || !rotVec)
                    return;
                
                auto currMotion = stateVec->positionDelta;
                auto bodyRot = rotVec->rotation;
                
                auto yaw = bodyRot._y + 
                (keys[0].second ? (keys[1].second ? 45.f : (keys[2].second ? 135.f : 90.f)) :
                (keys[3].second ? (keys[1].second ? -45.f : (keys[2].second ? -135.f : -90.f)) :
                (!keys[0].second && !keys[3].second && keys[2].second ? 180.f : 0.f)));

                auto motion = Vec3<float>(cos((yaw) * (3.14f / 180.f)) * this->speed, currMotion._y, sin((yaw) * (3.14f / 180.f)) * this->speed);
                lp->lerpMotion(&motion);

            }
        )
    );

};