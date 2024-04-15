#include "TestMod.h"

TestMod::TestMod(Manager* mgr) : Module(mgr, CategoryType::MISC, "Test Module", "For Developers") {

    this->setState(true);

    static bool once = false;
    static int c = 0;

    this->registerEvent<EventType::ScreenControllerTick, EventDispatcher::EventPriority::Medium, ScreenController*>(
        std::function<void(ScreenController*)>(
            [&](ScreenController* sc) -> void {
                if(sc->getName().rfind("chest") != std::string::npos) {
                    for(auto i = 0; i < 10; i++) {
                        for(auto i = 0; i < 9; i++)
                            sc->handleAutoPlace("container_items", i);
                    };
                };
                if(sc->getName().rfind("inventory") != std::string::npos) {
                    c++;

                    if(c > 50 && !once) {
                        once = true;
                        c = 0;
                        
                        Debugger::log("!");
                        
                        for(auto i = 0; i < 9; i++)
                            sc->handleAutoPlace("hotbar_items", i);
                        
                        sc->closeScreen();
                        Debugger::log("Screen Closed!");

                        once = true;
                    };
                };
            }
        )
    );

    this->registerEvent<EventType::Module_Tick, EventDispatcher::EventPriority::Medium>(
        std::function<void(void)>(
            [&](void) -> void {
                if(once) {
                    once = false;
                    c = 0;
                };
            }
        )
    );

    this->getEventDispatcher()->registerEvent(
        EventType::Present_Tick, EventDispatcher::EventPriority::Highest, std::function<void(void)>(
            [&](void) -> void {
                //
            }
        )
    );

};