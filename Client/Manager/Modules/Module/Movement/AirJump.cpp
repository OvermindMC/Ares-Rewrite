#include "AirJump.h"

AirJump::AirJump(Category* c) : Module(c, "AirJump") {
    this->registerEvent<EventType::OnLevel, Level*>(
        EventDispatcher::EventPriority::Medium,
        [&](Level* level) {
            if(!this->isEnabled())
                return;
            
            auto lp = MC::getClientInstance()->getPlayer();

            if(lp)
                lp->setIsOnGround(true);
        }
    );
};