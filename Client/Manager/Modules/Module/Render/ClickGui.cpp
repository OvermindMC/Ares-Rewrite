#include "ClickGui.h"

ClickGui::ClickGui(Manager* mgr) : Module(mgr, CategoryType::RENDER, "ClickGui", "Interact with Modules", VK_INSERT) {

    this->setState(true);

    this->registerEvent<EventType::Module_Toggle, EventDispatcher::EventPriority::Medium>(
        std::function<void(void)>([&](void) -> void {
            auto instance = MC::getClientInstance();

            if(this->getState()) {
                
                instance->releaseMouse();

            } else {
                
                if(instance->getScreenName().rfind("hud_screen") != std::string::npos)
                    instance->grabMouse();

            };
        })
    );

    this->registerEvent<EventType::Present_Tick, EventDispatcher::EventPriority::Highest>(
        std::function<void(void)>(
            [&](void) -> void {
                if(!this->getState())
                    return;
                
                static auto windows = std::vector<LiteRender::Window*>();
                auto instance = MC::getClientInstance();
                auto& io = ImGui::GetIO();

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
                        //window->setPos(x, 100.f);
                        window->updateBounds();

                        //x = (window->getBounds().z + window->getSpace());
                        windows.push_back(window);
                    };
                    std::sort(windows.begin(), windows.end(), [&](LiteRender::Window* windowA, LiteRender::Window* windowB) {
                        return windowA->getBounds().w > windowB->getBounds().w;
                    });

                    for(auto window : windows) {
                        window->setPos(x, 100.f);
                        window->updateBounds();
                        x = (window->getBounds().z + window->getSpace());
                    };
                };

                instance->releaseMouse();

                ImFX::Begin(ImGui::GetBackgroundDrawList());
                ImFX::AddBlur(10.f, ImVec4(0.f, 0.f, io.DisplaySize.x, io.DisplaySize.y));
                ImFX::End();
                
                for(auto window : windows)
                    window->render();
                
                if(instance->getScreenName().rfind("hud_screen") == std::string::npos) {
                    this->setState(false);
                };
            }
        )
    );

};