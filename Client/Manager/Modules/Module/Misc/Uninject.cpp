#include "Uninject.h"

Uninject::Uninject(Category* c) : Module(c, "Uninject") {
    this->setIsEnabled(false);

    this->evDispatcher->registerEvent<EventType::OnEnable>(
        EventDispatcher::EventPriority::High,
        [&]() {
            this->getMgr()->stop();
        }
    );
};