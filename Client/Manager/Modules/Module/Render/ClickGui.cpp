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
        std::function<void(char, bool, Vec2<float>, bool*)>(
            [&](char action, bool isDown, Vec2<float> mousePos, bool* cancel) -> void {
                if(!this->getState())
                    return;
                
                auto instance = MC::getClientInstance();
                mousePos = instance ? instance->mousePos : Vec2<float>();

                if(action)
                    *cancel = true;

                if(!instance)
                    return;
                
                bool actionDone = false;
                
                if((action == 1 || action == 2) && isDown) { /* Window collapsing */
                    for(auto iter = windows.rbegin(); iter != windows.rend(); ++iter) {
                        auto& window = *iter;
                        auto titleSize = Renderer::getTextSize(window->getTitle(), window->fontSize);
                        auto titleRect = Vec4<float>(window->rectPos.x, window->rectPos.y, window->rectPos.z, window->rectPos.y + (titleSize.y));

                        if(!this->dragWin) {
                            if(titleRect.intersects(mousePos)) {
                                if(action == 2) {
                                    window->isCollapsed = !window->isCollapsed;
                                } else {
                                    this->dragWin = window.get();
                                    this->dragStart = mousePos;
                                };
                                actionDone = true;
                                break;
                            };
                        };
                    };
                };

                if(this->dragWin && action == 0) {
                    auto diff = mousePos;
                    diff -= this->dragStart;

                    this->dragWin->tPos.x += diff._x;
                    this->dragWin->tPos.y += diff._y;

                    this->dragStart = mousePos;
                };

                if(this->dragWin && (action == 1 && !isDown)) {
                    this->dragWin = nullptr;
                    this->dragStart = Vec2<float>();
                };

                if(actionDone)
                    return;
                
                /* Do other potential actions */

                if(action == 1 && isDown) {
                    for(auto iter = windows.rbegin(); iter != windows.rend(); ++iter) {
                        auto& window = *iter;
                        auto titleSize = Renderer::getTextSize(window->getTitle(), window->fontSize);
                        auto titleRect = Vec4<float>(window->rectPos.x, window->rectPos.y, window->rectPos.z, window->rectPos.y + (titleSize.y));

                        if(titleRect.intersects(mousePos)) {
                            //
                        } else if(!window->isCollapsed) {
                            auto currY = (titleRect._w - 2.f) + (window->pad / 2.f);
                            for(auto module : window->category->getModules()) {
                                auto size = Renderer::getTextSize(module->name, window->fontSize);
                                auto rect = Vec4(window->rectPos.x, currY, window->rectPos.z, (currY + size.y));

                                if(rect.intersects(mousePos)) {
                                    module->toggleState();
                                    actionDone = true;
                                    return;
                                };

                                currY += size.y + (module == window->category->getModules().back() ? 0.f : (window->pad / 2.f));
                            };
                        };
                    };
                };
            }
        )
    );

    this->registerEvent<EventType::KeyInput, EventDispatcher::EventPriority::Highest>(
        std::function<void(uint64_t, bool, bool*)>(
            [&](uint64_t key, bool isDown, bool* cancel) -> void {
                if(this->getState()) {
                    *cancel = true;

                    if(key == VK_ESCAPE)
                        return this->toggleState();
                };
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
                        window->fontSize = std::min(14.f * this->uiScale, 20.f);
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
                
                auto& io = ImGui::GetIO();
                auto display = io.DisplaySize;

                ImFX::Begin(ImGui::GetBackgroundDrawList());
                ImFX::AddBlur(10.f, ImVec4(0.f, 0.f, display.x, display.y));
                ImFX::End();
                
                auto instance = MC::getClientInstance();
                auto guidata = instance ? instance->getGuiData() : nullptr;
                auto mousePos = instance ? instance->mousePos : Vec2<float>();

                if(windows.empty()) {
                    this->uiScale = guidata->uiScale;
                    auto totalWidth = 0.f;
                    auto space = 10.f;

                    for(auto category : this->mgr->getCategories()) {
                        auto window = std::make_unique<Window>(category);
                        totalWidth += (window->getBounds().x + space);
                    };

                    totalWidth -= space;
                    auto startX = (display.x - totalWidth) / 2.f;

                    auto currX = startX;
                    for(auto category : this->mgr->getCategories()) {
                        auto window = std::make_unique<Window>(category);
                        
                        window->tPos = ImVec2(currX, 20.f);
                        currX += (window->getBounds().x + space);
                        window->fontSize = std::min(14.f * this->uiScale, 20.f);
                        
                        windows.push_back(std::move(window));
                    }
                };

                auto upMostWin = (Window*)nullptr;
                for(auto iter = windows.rbegin(); iter != windows.rend(); ++iter) {
                    auto& window = *iter;
                    
                    if(
                        Vec4<float>(
                            window->rectPos.x, window->rectPos.y, window->rectPos.z, window->rectPos.w
                        ).intersects(mousePos)
                    ) {
                        upMostWin = window.get();
                        break;
                    };
                };

                for(auto& window : windows) {
                    
                    auto bounds = window->getBounds();
                    auto titleSize = Renderer::getTextSize(window->getTitle(), window->fontSize);
                    
                    window->rectPos.x = window->tPos.x; window->rectPos.y = window->tPos.y;
                    window->rectPos.z = window->tPos.x + bounds.x;

                    if(window->rectPos.w <= 0.f || this->dragWin == window.get())
                        window->rectPos.w = (window->isCollapsed ? window->tPos.y : window->tPos.y + bounds.y);

                    this->reachOff(&window->rectPos.w, window->isCollapsed ? window->tPos.y + titleSize.y : window->tPos.y + bounds.y, (window->category->getModules().size() * 2.f));

                    auto centerX = ((window->rectPos.x + (window->tPos.x + bounds.x)) / 2.f) - (Renderer::getTextW(window->getTitle(), window->fontSize) / 2.f);
                    auto titleRect = Vec4<float>(window->rectPos.x, window->rectPos.y, window->rectPos.z, window->rectPos.y + (titleSize.y));

                    Renderer::fillRect(window->rectPos, ImColor(0.f, 27.f, 74.f, 8.f), 1.f);
                    Renderer::fillRect(
                        ImVec4(
                            titleRect._x, titleRect._y, titleRect._z, titleRect._w
                        ), upMostWin == window.get() && titleRect.intersects(mousePos) ? ImColor(3.f, 88.f, 210.f, 1.f) : ImColor(2.f, 43.f, 115.f, 1.f), 1.f);

                    Renderer::drawText(ImVec2(centerX, window->tPos.y), window->getTitle(), window->fontSize, ImColor(255.f, 255.f, 255.f));

                    Renderer::fillRect(
                        ImVec4(
                            window->rectPos.x, window->rectPos.y + titleSize.y, window->rectPos.z, window->rectPos.y + (titleSize.y + 2.f)
                        ), ImColor(255.f, 255.f, 255.f, 1.f), 1.f
                    );

                    auto currY = (titleRect._w - 2.f) + (window->pad / 2.f);
                    for(auto module : window->category->getModules()) {
                        auto size = Renderer::getTextSize(module->name, window->fontSize);
                        auto rect = Vec4(window->rectPos.x, currY, window->rectPos.z, (currY + size.y));

                        if(currY + (size.y) > window->rectPos.w)
                            break;

                        Renderer::drawText(
                            ImVec2(
                                window->tPos.x + 2.f, currY
                            ), module->name, window->fontSize, module->getState() ? ImColor(3.f, 252.f, 207.f) : ImColor(255.f, 255.f, 255.f)
                        );

                        if(upMostWin == window.get() && rect.intersects(mousePos) && module->description.length() > 0) {
                            auto text = module->description;
                            auto textSize = Renderer::getTextSize(text, window->fontSize);

                            auto hRect = ImVec4(
                                mousePos._x - (textSize.x / 2.f), (mousePos._y - 14.f) - (textSize.y / 2.f),
                                (mousePos._x - (textSize.x / 2.f)) + textSize.x, ((mousePos._y - 14.f) - (textSize.y / 2.f)) + textSize.y
                            );

                            Renderer::fillRect(hRect, ImColor(2.f, 43.f, 115.f, 1.f), 1.f);
                            Renderer::drawText(
                                ImVec2(hRect.x, hRect.y), module->description, window->fontSize, ImColor(255.f, 255.f, 255.f)
                            );
                        };

                        currY += size.y + (module == window->category->getModules().back() ? 0.f : (window->pad / 2.f));
                    };

                };
            }
        )
    );

};

auto ClickGui::reachOff(float* x, float xOff, float modifier) -> void {

    if (*x < xOff) {

		if (*x < (xOff - modifier))
			*x += modifier;
		else
			*x = xOff;

	} else if (*x > xOff) {

		if (*x > (xOff + modifier))
			*x -= modifier;
		else
			*x = xOff;

	};

};