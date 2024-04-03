#include "TestModule.h"

TestMod::TestMod(Manager* mgr) : Module(mgr, CategoryType::MISC, "Test Module", "For Developers") {

    this->setState(true);

    this->getEventDispatcher()->registerEvent(
        EventType::Module_Tick, EventDispatcher::EventPriority::Low, std::function<void(void)>(
            [&]() -> void {
                Debugger::log("Tick!");
                
                static int c = 0;
                c++;

                if(c > 50) {
                    this->getEventDispatcher()->unregisterEvent(EventType::Module_Tick);
                    Debugger::log("Unregistered!");

                    this->category->mgr->client->stop();
                };
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