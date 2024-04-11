#include "TestMod.h"

TestMod::TestMod(Manager* mgr) : Module(mgr, CategoryType::MISC, "Test Module", "For Developers") {

    this->setState(true);

    this->getEventDispatcher()->registerEvent(
        EventType::Present_Tick, EventDispatcher::EventPriority::Highest, std::function<void(void)>(
            [&](void) -> void {
                auto rectPos = ImVec4(10.f, 10.f, 10.f + Renderer::getTextW("Hello, World!", 18.f), 10.f + Renderer::getTextH("Hello, World!", 18.f));
                auto padd = ImVec2(4.f, 6.f);

                Renderer::fillRect(rectPos, ImColor(80.f, 100.f, 170.f), 0.f);
                Renderer::addRect(ImVec4(
                    rectPos.x - padd.x, rectPos.y - padd.y,
                    rectPos.z + padd.x, rectPos.w + padd.y
                ), ImColor(21.f, 21.f, 21.f, 0.6f), 1.f, 3.f);

                Renderer::drawText(
                    ImVec2(10.f, 10.f), "Hello, World!", 18.f, ImColor(255.f, 255.f, 255.f)
                );
                
            }
        )
    );

};