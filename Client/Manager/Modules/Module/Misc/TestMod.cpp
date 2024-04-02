#include "TestModule.h"

TestMod::TestMod(Manager* mgr) : Module(mgr, CategoryType::MISC, "Test Module", "For Developers") {

    this->setState(true);

    this->getEventDispatcher()->registerEvent(
        EventType::Module_Tick, EventDispatcher::EventPriority::Low, std::function<void(void)>(
            [&]() -> void {
                Debugger::log("Tick!");
                this->setState(false);
            }
        )
    );

    this->getEventDispatcher()->registerEvent(
        EventType::Module_Toggle, EventDispatcher::EventPriority::Low, std::function<void(void)>(
            [&]() -> void {
                Debugger::log(this->name + " " + (this->getState() ? "Enabled!" : "Disabled!"));
            }
        )
    );

};