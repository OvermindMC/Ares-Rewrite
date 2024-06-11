#include "TestMod.h"

TestMod::TestMod(Manager* mgr) : Module(mgr, CategoryType::MISC, "Test Module", "For Developers") {

    this->setState(true);

    this->registerEvent<EventType::Module_Toggle, EventDispatcher::EventPriority::Medium>(
        std::function<void(void)>(
            [&](void) -> void {
                auto instance = MC::getClientInstance();

                std::ostringstream ss;
                ss << "Client Instance: " << std::hex << instance;

                Debugger::log(ss.str());
            }
        )
    );

};