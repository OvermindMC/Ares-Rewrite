#include "TestMod.h"

TestMod::TestMod(Manager* mgr) : Module(mgr, CategoryType::MISC, "Test Module", "For Developers") {

    this->getEventDispatcher()->registerEvent(
        EventType::Present_Tick, EventDispatcher::EventPriority::Highest, std::function<void(void)>(
            [&](void) -> void {
                Renderer::drawText(
                    ImVec2(10.f, 10.f), "Hello, World!", 18.f, ImColor(255.f, 255.f, 255.f)
                );
            }
        )
    );

};