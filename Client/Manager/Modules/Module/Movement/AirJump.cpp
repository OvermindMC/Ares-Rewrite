#include "AirJump.h"

AirJump::AirJump(Category* c) : Module(c, "AirJump") {
    this->setIsEnabled(true);

    this->registerEvent<EventType::OnLevel, Level*>(
        EventDispatcher::EventPriority::Medium,
        [&](Level* level) {
            auto lp = MC::getClientInstance()->getPlayer();

            if(lp)
                lp->setIsOnGround(true);
        }
    );
};