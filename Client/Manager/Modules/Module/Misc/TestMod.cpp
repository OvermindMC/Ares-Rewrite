#include "TestMod.h"

class PromptBtn {
public:
    ImVec4 rect;
    std::string displayText;
    std::function<void(void)> onClick = std::function<void(void)>([&](void) -> void {});
    PromptBtn(std::string text, std::function<void(void)> clickFunc = std::function<void(void)>([&](void) -> void {})) : displayText(text), onClick(clickFunc) {};
};

TestMod::TestMod(Manager* mgr) : Module(mgr, CategoryType::MISC, "Test Module", "For Developers") {

    this->setState(true);

    static bool updateNeeded = false, dismissed = false;
    
    static std::vector<std::unique_ptr<PromptBtn>> promptBtns;
    static std::vector<Module*> modules;
    
    this->registerEvent<EventType::Client_Update, EventDispatcher::EventPriority::Low>(
        std::function<void(Version, json)>(
            [&](Version version, json patch_notes) -> void {
                updateNeeded = true;
                dismissed = false;
            }
        )
    );

    this->registerEvent<EventType::Present_Tick, EventDispatcher::EventPriority::Low>(
        std::function<void(void)>(
            [&](void) -> void {
                auto aresUser = this->client->socket->user;
                if(updateNeeded && !dismissed && aresUser->hasUpdate()) {
                    if(modules.empty()) {
                        for(auto category : this->mgr->getCategories()) {
                            for(auto module : category->getModules()) {
                                if(module == this)
                                    continue;
                                if(module->getState())
                                    modules.push_back(module);
                            };
                        };
                    };

                    for(auto module : modules) {
                        if(module->getState())
                            module->setState(false);
                    };

                    auto& io = ImGui::GetIO();
                    auto display = io.DisplaySize;

                    ImFX::Begin(ImGui::GetBackgroundDrawList());
                    ImFX::AddBlur(10.f, ImVec4(0.f, 0.f, display.x, display.y));
                    ImFX::End();

                    auto rect = ImVec4(
                        200.f, 200.f, display.x - 200.f, display.y - 200.f
                    );

                    Renderer::fillRect(rect, ImColor(21.f, 21.f, 21.f, .6f), 3.f);

                    auto version = this->client->socket->user->aresVer.get();
                    
                    auto title = std::string(this->client->getName() + " v" + version.first);
                    auto titleSize = Renderer::getTextSize(title, 18.f);

                    Renderer::drawText(
                        ImVec2(
                            rect.x + (((rect.z - rect.x) / 2.f) - (titleSize.x / 2.f)), rect.y + titleSize.y
                        ), title, 18.f, ImColor(255.f, 255.f, 255.f)
                    );

                    Renderer::fillRect(
                        ImVec4(
                            (rect.x - 2.f) + (((rect.z - rect.x) / 2.f) - (titleSize.x / 2.f)), rect.y + (titleSize.y * 2.f),
                            (rect.x + (titleSize.x - 1.f)) + (((rect.z - rect.x) / 2.f) - (titleSize.x / 2.f)), (rect.y + 2.f) + (titleSize.y * 2.f)
                        ), ImColor(255.f, 255.f, 255.f), 1.f
                    );

                    auto patch_data = version.second;
                    auto description = patch_data.contains("notes") ? patch_data["notes"].get<std::string>() : "No Description Provided :/";

                    Renderer::drawText(
                        ImVec2(
                            rect.x + 4.f,
                            (rect.y + 2.f) + ((titleSize.y * 2.f) * 2.f)
                        ), "Description", 18.f, ImColor(255.f, 255.f, 255.f)
                    );

                    auto descriptionDisplaceSize = Renderer::getTextSize("Description", 18.f);
                    Renderer::fillRect(
                        ImVec4(
                            rect.x + 4.f, (rect.y + 2.f) + ((titleSize.y * 2.f) * 2.f) + (descriptionDisplaceSize.y + 2.f),
                            (rect.x + 4.f) + (descriptionDisplaceSize.x + 2.f), (rect.y + 2.f) + ((titleSize.y * 2.f) * 2.f) + (descriptionDisplaceSize.y + 2.f)
                        ), ImColor(255.f, 255.f, 255.f), 1.f
                    );

                    auto descY = (rect.y + 2.f) + ((titleSize.y * 2.f) * 2.f) + ((descriptionDisplaceSize.y * 2.f) + 2.f);
                    Renderer::drawText(
                        ImVec2(
                            rect.x + 6.f, descY
                        ), description, 18.f, ImColor(255.f, 255.f, 255.f)
                    );

                    if(promptBtns.empty()) {
                        for(auto text : {"Download", "Dismiss"}) {
                            auto btn = std::make_unique<PromptBtn>(text);
                            auto onClick = std::function<void(void)>([&](void) -> void {});

                            if(text == "Download") {
                                onClick = std::function<void(void)>([&](void) -> void {
                                    Debugger::log("Download!");
                                });
                            } else if(text == "Dismiss") {
                                onClick = std::function<void(void)>([&](void) -> void {
                                    dismissed = true;
                                    
                                    for(auto module : modules)
                                        module->setState(true);
                                });
                            };

                            btn->onClick = onClick;
                            promptBtns.push_back(std::move(btn));
                        };
                    };

                    auto space = 10.f;
                    float totalWidth = 0.f;

                    for(auto& btn : promptBtns) {
                        auto textSize = Renderer::getTextSize(btn->displayText, 18.f);
                        totalWidth += textSize.x + space;
                    };
                    
                    totalWidth -= space;
                    auto currX = rect.x + ((rect.z - rect.x) - totalWidth) / 2.f;

                    for(auto& btn : promptBtns) {
                        auto textSize = Renderer::getTextSize(btn->displayText, 18.f);
                        btn->rect = ImVec4(
                            currX - 2.f, (rect.w - 2.f) - ((titleSize.y * 2.f) + space),
                            (currX + 2.f) + textSize.x, (rect.w + 2.f) - ((titleSize.y * 2.f) + space) + textSize.y
                        );

                        Renderer::drawText(
                            ImVec2(
                                currX, rect.w - ((titleSize.y * 2.f) + space)
                            ), btn->displayText, 18.f, ImColor(255.f, 255.f, 255.f)
                        );

                        currX += textSize.x + space;
                    }
                } else if(!aresUser->hasUpdate() && !modules.empty()) { /* Abrupt close, server disconnected upon displaying update! */
                    for(auto module : modules) {
                        module->setState(true);
                    };
                };
            }
        )
    );

    this->registerEvent<EventType::MouseInput, EventDispatcher::EventPriority::Highest>(
        std::function<void(char, bool, Vec2<float>, bool*)>(
            [&](char action, bool isDown, Vec2<float> mousePos, bool* cancel) -> void {
                if(action && updateNeeded && !dismissed)
                    *cancel = true;

                if(!action || !isDown)
                    return;
                
                if(updateNeeded && !dismissed) {
                    auto instance = MC::getClientInstance();
                    
                    if(!instance)
                        return;
                    
                    mousePos = instance->mousePos;
                    for(auto& btn : promptBtns) {
                        if(Vec4<float>(btn->rect.x, btn->rect.y, btn->rect.z, btn->rect.w).intersects(mousePos)) {
                            btn->onClick();
                        };
                    };
                };
            }
        )
    );

};