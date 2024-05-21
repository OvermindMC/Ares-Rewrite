#include "Timer.h"

TimerMod::TimerMod(Manager* mgr) : Module(mgr, CategoryType::MISC, "Timer", "Modify Game Speed") {

    this->registerEvent<EventType::Level_Tick, EventDispatcher::EventPriority::Low>(
        std::function<void(Level* level)>(
            [&](Level* level) -> void {
                if(!this->getState())
                    return;
                
                auto instance = MC::getClientInstance();
                auto mc = instance ? instance->getMinecraft() : nullptr;

                if(mc) {
                    mc->realTimer->ticksPerSec = 30.f;
                    mc->simTimer->ticksPerSec = 30.f;
                };
            }
        )
    );

    this->registerEvent<EventType::Module_Toggle, EventDispatcher::EventPriority::Low>(
        std::function<void(void)>(
            [&](void) -> void {
                if(!this->getState()) {
                    auto instance = MC::getClientInstance();
                    auto mc = instance ? instance->getMinecraft() : nullptr;

                    if(mc) {
                        mc->realTimer->ticksPerSec = 20.f;
                        mc->simTimer->ticksPerSec = 20.f;
                    };
                };
            }
        )
    );

};