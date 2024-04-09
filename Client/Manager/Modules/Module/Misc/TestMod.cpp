#include "TestMod.h"

TestMod::TestMod(Manager* mgr) : Module(mgr, CategoryType::MISC, "Test Module", "For Developers") {

    this->setState(true);

    this->getEventDispatcher()->registerEvent(
        EventType::Module_Tick, EventDispatcher::EventPriority::Low, std::function<void(void)>(
            [&]() -> void {
                //
            }
        )
    );

    this->getEventDispatcher()->registerEvent(
        EventType::Module_Toggle, EventDispatcher::EventPriority::Low, std::function<void(void)>(
            [&]() -> void {
                //
            }
        )
    );

};