#include "Uninject.h"

Uninject::Uninject(Manager* mgr) : Module(mgr, CategoryType::MISC, "Uninject", "Remove the Client from the Game") {

    this->getEventDispatcher()->registerEvent(
        EventType::Module_Toggle, EventDispatcher::EventPriority::Low, std::function<void(void)>(
            [&]() -> void {
                if(this->getState())
                    return this->client->stop();
            }
        )
    );

};