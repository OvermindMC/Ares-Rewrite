#include "ClickGui.h"

class Window {
public:
    ImVec4 rectPos;
    ImVec2 tPos;
public:
    bool isCollapsed = false;
    float fontSize = 18.f;
public:
    float pad = 16.f;
public:
    Category* category;
public:
    Window(Category* c) : category(c) {};
public:
    auto getTitle(void) -> std::string {
        return category->getName();
    };
public:
    auto getBounds(void) -> ImVec2 {
        auto currSize = Renderer::getTextSize(category->getName(), fontSize);
        currSize.x += pad;

        for(auto module : category->getModules()) {
            auto size = Renderer::getTextSize(module->name, fontSize);
            size.x += pad; size.y += (pad / 2.f);

            if(size.x > currSize.x)
                currSize.x = size.x;
            
            currSize.y += size.y;
        };
        
        return currSize;
    };
};

ClickGui::ClickGui(Manager* mgr) : Module(mgr, CategoryType::RENDER, "ClickGui", "Interact with Modules", VK_INSERT) {

    static auto windows = std::vector<std::unique_ptr<Window>>();

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

    this->registerEvent<EventType::MouseInput, EventDispatcher::EventPriority::Highest>(
        std::function<void(char, bool, Vec2<float>)>(
            [&](char action, bool isDown, Vec2<float> mousePos) -> void {
                auto instance = MC::getClientInstance();
                mousePos = instance ? instance->mousePos : Vec2<float>();

                if(!instance)
                    return;
                
                bool actionDone = false;
                
                if(action == 2 && isDown) { /* Window collapsing */
                    for(auto iter = windows.rbegin(); iter != windows.rend(); ++iter) {
                        auto& window = *iter;
                        auto titleSize = Renderer::getTextSize(window->getTitle(), window->fontSize);
                        auto titleRect = Vec4<float>(window->rectPos.x, window->rectPos.y, window->rectPos.z, window->rectPos.y + (titleSize.y));

                        if(titleRect.intersects(mousePos)) {
                            window->isCollapsed = !window->isCollapsed;
                            actionDone = true;
                            return;
                        };
                    };
                };

                if(actionDone)
                    return;
                
                /* Do other potential actions */
            }
        )
    );

    this->registerEvent<EventType::KeyInput, EventDispatcher::EventPriority::Highest>(
        std::function<void(uint64_t, bool)>(
            [&](uint64_t key, bool isDown) -> void {
                //
            }
        )
    );

    this->registerEvent<EventType::Present_Resize, EventDispatcher::EventPriority::Highest>(
        std::function<void(void)>(
            [&](void) -> void {
                auto instance = MC::getClientInstance();
                auto guidata = instance ? instance->getGuiData() : nullptr;

                if(guidata->uiScale != this->uiScale) {
                    this->uiScale = guidata->uiScale;

                    for(auto& window : windows) {
                        window->fontSize = std::min(12.f * this->uiScale, 18.f);
                    };
                };
            }
        )
    );

    this->registerEvent<EventType::Present_Tick, EventDispatcher::EventPriority::Highest>(
        std::function<void(void)>(
            [&](void) -> void {
                if(!this->getState())
                    return;
                
                auto instance = MC::getClientInstance();
                auto guidata = instance ? instance->getGuiData() : nullptr;
                auto mousePos = instance ? instance->mousePos : Vec2<float>();

                if(windows.empty()) {
                    auto currX = 10.f;
                    this->uiScale = guidata->uiScale;

                    for(auto category : this->mgr->getCategories()) {
                        auto window = std::make_unique<Window>(category);
                        
                        window->tPos = ImVec2(currX, 20.f);
                        currX += (window->getBounds().x * 1.08f);
                        window->fontSize = std::min(12.f * this->uiScale, 18.f);
                        
                        windows.push_back(std::move(window));
                    }
                };

                for(auto& window : windows) {
                    
                    auto bounds = window->getBounds();
                    auto titleSize = Renderer::getTextSize(window->getTitle(), window->fontSize);
                    window->rectPos = ImVec4(window->tPos.x, window->tPos.y, window->tPos.x + bounds.x, window->tPos.y + (window->isCollapsed ? (titleSize.y) : bounds.y));

                    auto centerX = ((window->rectPos.x + (window->tPos.x + bounds.x)) / 2.f) - (Renderer::getTextW(window->getTitle(), window->fontSize) / 2.f);
                    auto titleRect = Vec4<float>(window->rectPos.x, window->rectPos.y, window->rectPos.z, window->rectPos.y + (titleSize.y));

                    Renderer::fillRect(window->rectPos, ImColor(0.f, 27.f, 74.f, 8.f), 1.f);
                    Renderer::fillRect(
                        ImVec4(
                            titleRect._x, titleRect._y, titleRect._z, titleRect._w
                        ), titleRect.intersects(mousePos) ? ImColor(3.f, 88.f, 210.f, 1.f) : ImColor(2.f, 43.f, 115.f, 1.f), 1.f);

                    Renderer::drawText(ImVec2(centerX, window->tPos.y), window->getTitle(), window->fontSize, ImColor(255.f, 255.f, 255.f));

                    Renderer::fillRect(
                        ImVec4(
                            window->rectPos.x, window->rectPos.y + titleSize.y, window->rectPos.z, window->rectPos.y + (titleSize.y + 2.f)
                        ), ImColor(255.f, 255.f, 255.f, 1.f), 1.f
                    );

                    if(window->isCollapsed)
                        continue;

                    auto currY = (titleRect._w - 2.f) + (window->pad / 2.f);
                    for(auto module : window->category->getModules()) {
                        auto size = Renderer::getTextSize(module->name, window->fontSize);

                        Renderer::drawText(
                            ImVec2(
                                window->tPos.x + 2.f, currY
                            ), module->name, window->fontSize, ImColor(255.f, 255.f, 255.f)
                        );
                        currY += size.y + (module == window->category->getModules().back() ? 0.f : (window->pad / 2.f));
                    };

                };
            }
        )
    );

};