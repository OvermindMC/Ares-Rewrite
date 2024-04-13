#include "TestMod.h"

TestMod::TestMod(Manager* mgr) : Module(mgr, CategoryType::MISC, "Test Module", "For Developers") {

    this->setState(true);

    this->getEventDispatcher()->registerEvent(
        EventType::Module_Toggle, EventDispatcher::EventPriority::Medium, std::function<void(void)>(
            [&](void) -> void {
                auto instance = MC::getClientInstance();

                std::ostringstream o;
                o << std::hex << instance;

                Debugger::log("Client Instance: " + o.str());
            }
        )
    );

    this->getEventDispatcher()->registerEvent(
        EventType::Present_Tick, EventDispatcher::EventPriority::Highest, std::function<void(void)>(
            [&](void) -> void {
                static auto windows = std::vector<LiteRender::Window*>();

                if(windows.empty()) {
                    float x = 100.f;
                    for(auto category : this->mgr->getCategories()) {
                        if(category->getModules().empty())
                            continue;
                        
                        auto window = new LiteRender::Window(category->getName());
                        auto frames = std::vector<LiteRender::Frame*>();

                        for(auto module : category->getModules()) {
                            frames.push_back(new LiteRender::Frame({
                                new LiteRender::Container(
                                    new LiteRender::Text(
                                        module->name
                                    )
                                )
                            }));
                            frames.push_back(
                                new LiteRender::Frame({
                                    new LiteRender::Container(
                                        new LiteRender::Checkbox(
                                            "Enabled", ImColor(255.f, 255.f, 255.f), &module->state.first
                                        )
                                    )
                                }, 14.f)
                            );
                        };

                        for(auto frame : frames)
                            window->frames.push_back(frame);
                        
                        window->setExtraSpace(6.f);
                        window->setPos(x, 100.f);
                        window->updateBounds();

                        x = (window->getBounds().z + window->getSpace());
                        windows.push_back(window);
                    };
                };

                for(auto window : windows)
                    window->render();
            }
        )
    );

};