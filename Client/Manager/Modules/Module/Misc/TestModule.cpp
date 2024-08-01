#include "TestModule.h"

TestMod::TestMod(Category* c) : Module(c, "Test Module") {
    this->setIsEnabled(true);
    
    this->registerEvent<EventType::OnTick>(
        EventDispatcher::EventPriority::High,
        [&]() {
            //
        }
    );

    this->registerEvent<EventType::OnLevel, Level*>(
        EventDispatcher::EventPriority::Medium,
        [&](Level* level) {
            //
        }
    );
};