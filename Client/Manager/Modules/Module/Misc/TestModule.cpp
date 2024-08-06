#include "TestModule.h"

TestMod::TestMod(Category* c) : Module(c, "Test Module") {
    this->setIsEnabled(true);
    
    this->registerEvent<EventType::OnEnable>(
        EventDispatcher::EventPriority::Low,
        [&]() {
            //
        }
    );

    this->registerEvent<EventType::OnDisable>(
        EventDispatcher::EventPriority::Low,
        [&]() {
            //
        }
    );
    
    this->registerEvent<EventType::OnTick>(
        EventDispatcher::EventPriority::Low,
        [&]() {
            //
        }
    );

    this->registerEvent<EventType::OnLevel, Level*>(
        EventDispatcher::EventPriority::Low,
        [&](Level* level) {
            if(!this->isEnabled())
                return;
        }
    );

    this->registerEvent<EventType::OnGameMode, GameMode*>(
        EventDispatcher::EventPriority::Low,
        [&](GameMode* GM) {
            if(!this->isEnabled())
                return;
        }
    );

    this->registerEvent<EventType::OnFirstPersonLook, Vec2*>(
        EventDispatcher::EventPriority::Low,
        [&](Vec2* mAngles) {
            if(!this->isEnabled())
                return;
        }
    );
};