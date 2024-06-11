#include "AutoSprint.h"

AutoSprint::AutoSprint(Manager* mgr) : Module(mgr, CategoryType::PLAYER, "AutoSprint", "Automatically Sprint") {
    
    this->registerEvent<EventType::Level_Tick, EventDispatcher::EventPriority::Low>(
        std::function<void(Level*)>(
            [&](Level* level) -> void {
                if(!this->getState())
                    return;
                
                auto instance = MC::getClientInstance();
                auto lp = instance ? instance->getLocalPlayer() : nullptr;

                if(!lp)
                    return;
                
                auto data = lp->getComponentData<StateVectorComponent>();
                
                auto motion = data->positionDelta;
                auto speed = sqrtf(motion._x * motion._x + motion._z * motion._z);

                if(speed > 0.05f)
                    lp->setSprinting(true);
            }
        )
    );

};