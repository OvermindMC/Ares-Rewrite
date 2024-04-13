#include "TestMod.h"

TestMod::TestMod(Manager* mgr) : Module(mgr, CategoryType::MISC, "Test Module", "For Developers") {

    this->setState(true);

    this->getEventDispatcher()->registerEvent(
        EventType::Present_Tick, EventDispatcher::EventPriority::Highest, std::function<void(void)>(
            [&](void) -> void {
                static auto window = LiteRender::Window(
                    "Test Window", 18.f, {
                        new LiteRender::Frame({
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
                                new LiteRender::Button(
                                    "Button 1", ImColor(255.f, 255.f, 255.f),
                                    [=](char action, bool isDown) -> void {
                                        //
                                    }
                                )
                            ),
                            new LiteRender::Container(
                                new LiteRender::Button(
                                    "Button 2", ImColor(255.f, 255.f, 255.f),
                                    [=](char action, bool isDown) -> void {
                                        //
                                    }
                                )
                            )
                        }),
                        new LiteRender::Frame({
                            new LiteRender::Container(
                                new LiteRender::Button(
                                    "Button", ImColor(255.f, 255.f, 255.f),
                                    [=](char action, bool isDown) -> void {
                                        //
                                    }
                                )
                            ),
                            new LiteRender::Container(
                                new LiteRender::Text(
                                    "Text"
                                )
                            )
                        })
                    }
                );
                
                window.setStylesFor(
                    LiteRender::Element::ElementType::Button,
                    LiteRender::Element::ElementStyle(
                        ImColor(122.f, 31.f, 196.f), ImColor(54.f, 52.f, 51.f)
                    )
                );
                
                window.setWindowStyles(
                    LiteRender::Element::ElementStyle(
                        ImColor(100.f, 110.f, 178.f), ImColor(21.f, 21.f, 21.f)
                    )
                );

                window.setExtraSpace(6.f);
                window.setPos(100.f, 100.f);
                window.render();
            }
        )
    );

};