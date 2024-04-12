#include "TestMod.h"

TestMod::TestMod(Manager* mgr) : Module(mgr, CategoryType::MISC, "Test Module", "For Developers") {

    this->setState(true);

    this->getEventDispatcher()->registerEvent(
        EventType::Present_Tick, EventDispatcher::EventPriority::Highest, std::function<void(void)>(
            [&](void) -> void {

                static auto frameA = LiteRender::Frame({
                    new LiteRender::Container(
                        new LiteRender::Text(
                            "Text A"
                        )
                    ),
                    new LiteRender::Container(
                        new LiteRender::Text(
                            "Text B"
                        )
                    ),
                    new LiteRender::Container(
                        new LiteRender::Text(
                            "Text C"
                        )
                    )
                });

                frameA.setPos(100.f, 100.f);
                frameA.render();

                static auto frameB = LiteRender::Frame({
                    new LiteRender::Container(
                        new LiteRender::Text(
                            "Text D"
                        )
                    ),
                    new LiteRender::Container(
                        new LiteRender::Text(
                            "Text E"
                        )
                    ),
                    new LiteRender::Container(
                        new LiteRender::Text(
                            "Text F"
                        )
                    )
                });

                frameB.setStylesAll(LiteRender::Element::ElementStyle(
                    ImColor(8.f, 157.f, 252.f), ImColor(252.f, 130.f, 8.f)
                ));
                
                frameB.setPos(frameA.getBounds().z + frameB.getSpace(), 100.f);
                frameB.render();

            }
        )
    );

};