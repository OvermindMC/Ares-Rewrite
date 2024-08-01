#include "TestModule.h"

TestMod::TestMod(Category* c) : Module(c, "Test Module") {
    this->setIsEnabled(true);

    this->evDispatcher->registerEvent<EventType::OnTick>(
        EventDispatcher::EventPriority::High,
        [&]() {
            //
        }
    );
};