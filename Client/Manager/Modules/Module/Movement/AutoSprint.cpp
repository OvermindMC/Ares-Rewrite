#include "AutoSprint.h"

AutoSprint::AutoSprint(Category* c) : Module(c, "AutoSprint") {
    this->setIsEnabled(true);

    this->registerEvent<EventType::OnGameMode, GameMode*>(
        EventDispatcher::EventPriority::Low,
        [&](GameMode* GM) {
            Player* player = GM->player;
            float speed = [&] { auto m = player->getMotion(); return std::sqrt(m.x * m.x + m.z * m.z); }();

            if(speed > 0.1f)
                player->setSprinting(true);
        }
    );
};