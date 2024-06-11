#include "ClickGui.h"

class ClickGuiWindow {
public:
    class Mod {
        public:
            Module* mod = nullptr;
            bool isCollapsed = true;
        
            Mod(Module* mod) : mod(mod) {};
    };
    
    ImVec4 rectPos;
    ImVec2 tPos;
    
    bool isCollapsed = false;
    float fontSize = 18.f;
    float pad = 16.f;
    
    Category* category;
    std::vector<std::unique_ptr<Mod>> mods;
    
    ClickGuiWindow(Category* c) : category(c) {};
    
    auto getTitle(void) -> std::string {
        return category->getName();
    };
    
    auto getBounds(void) -> ImVec2 {
        auto currSize = Renderer::getTextSize(std::string(category->getName() + "   "), fontSize);
        currSize.x += pad;

        for(auto& mod : mods) {
            auto module = mod->mod;
            auto size = Renderer::getTextSize(std::string(module->name + "   "), fontSize);
            size.x += pad; size.y += (pad / 2.f);

            if(size.x > currSize.x)
                currSize.x = size.x;
            
            if(!mod->isCollapsed) {
                for(auto& [ name, setting ] : module->settings) {
                    if(!setting->isVisible())
                        continue;
                    
                    auto key = name;

                    if(setting->isType<float>() || setting->isType<int>() || setting->isType<uint64_t>()) {
                        key += std::string(": " + setting->isType<uint64_t>() ? "None  " : "0000  ");
                    };

                    auto sSize = Renderer::getTextSize(key, fontSize);
                    sSize.x += pad; sSize.y += (pad / 2.f);

                    if(sSize.x > currSize.x)
                        currSize.x = sSize.x;
                    
                    currSize.y += sSize.y;
                };
            };
            
            currSize.y += (
                size.y + (
                    mod == this->mods.back() ? 4.f : 0.f
                )
            );
        };
        
        return currSize;
    };
};

class HoveringTooltip {
    public:
        std::string text;
        float fontSize;
    public:
        HoveringTooltip(std::string tooltip_text, float font_size) : text(tooltip_text), fontSize(font_size) {};
};

ClickGui::ClickGui(Manager* mgr) : Module(mgr, CategoryType::RENDER, "ClickGui", "Interact with Modules", VK_INSERT) {

    static auto windows = std::vector<std::unique_ptr<ClickGuiWindow>>();
    static auto vkToStringMap = std::map<int, std::string>{
        {VK_BACK, "Backspace"},
        {VK_TAB, "Tab"},
        {VK_CLEAR, "Clear"},
        {VK_RETURN, "Enter"},
        {VK_SHIFT, "Shift"},
        {VK_CONTROL, "Control"},
        {VK_MENU, "Alt"},
        {VK_PAUSE, "Pause"},
        {VK_CAPITAL, "Caps Lock"},
        {VK_ESCAPE, "Escape"},
        {VK_SPACE, "Space"},
        {VK_PRIOR, "Page Up"},
        {VK_NEXT, "Page Down"},
        {VK_END, "End"},
        {VK_HOME, "Home"},
        {VK_LEFT, "Left Arrow"},
        {VK_UP, "Up Arrow"},
        {VK_RIGHT, "Right Arrow"},
        {VK_DOWN, "Down Arrow"},
        {VK_SELECT, "Select"},
        {VK_PRINT, "Print Screen"},
        {VK_EXECUTE, "Execute"},
        {VK_SNAPSHOT, "Print Screen"},
        {VK_INSERT, "Insert"},
        {VK_DELETE, "Delete"},
        {VK_HELP, "Help"},

        {VK_F1, "F1"},
        {VK_F2, "F2"},
        {VK_F3, "F3"},
        {VK_F4, "F4"},
        {VK_F5, "F5"},
        {VK_F6, "F6"},
        {VK_F7, "F7"},
        {VK_F8, "F8"},
        {VK_F9, "F9"},
        {VK_F10, "F10"},
        {VK_F11, "F11"},
        {VK_F12, "F12"},
        {VK_F13, "F13"},
        {VK_F14, "F14"},
        {VK_F15, "F15"},
        {VK_F16, "F16"},
        {VK_F17, "F17"},
        {VK_F18, "F18"},
        {VK_F19, "F19"},
        {VK_F20, "F20"},
        {VK_F21, "F21"},
        {VK_F22, "F22"},
        {VK_F23, "F23"},
        {VK_F24, "F24"}
    };

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
                
                instance->releaseMouse();
                bool actionDone = false;
                
                for(auto iter = windows.rbegin(); iter != windows.rend(); ++iter) {
                    auto& window = *iter;
                    auto titleSize = Renderer::getTextSize(std::string(window->getTitle() + "   "), window->fontSize);
                    auto titleRect = Vec4<float>(window->rectPos.x, window->rectPos.y, window->rectPos.z, window->rectPos.y + (titleSize.y));

                    if(!this->dragWin && ((action == 1 || action == 2) && isDown)) {
                        if(titleRect.intersects(mousePos)) {
                            if(action == 2) {
                                window->isCollapsed = !window->isCollapsed;

                                for(auto& mod : window->mods) {
                                    mod->isCollapsed = true;
                                };
                            } else {
                                this->dragWin = window.get();
                                this->dragStart = mousePos;
                            };
                            actionDone = true;
                            break;
                        };
                    } else if(this->isDraggingSlider && action == 0) {
                        auto found = false;

                        auto currY = (titleRect._w - 2.f) + (window->pad / 2.f);
                            for(auto& mod : window->mods) {
                                auto module = mod->mod;
                                auto size = Renderer::getTextSize(std::string(module->name + "   "), window->fontSize);

                                if(!mod->isCollapsed) {
                                    for(auto& [ name, setting ] : module->settings) {
                                        if(!setting->isVisible())
                                            continue;
                                        
                                        auto sSize = Renderer::getTextSize(name, window->fontSize);
                                        auto sRect = Vec4(window->rectPos.x, currY + (sSize.y + (window->pad / 2.f)), window->rectPos.z, ((currY + (sSize.y + (window->pad / 2.f))) + size.y));

                                        if(sRect.intersects(mousePos) && setting->isType<float>() || setting->isType<int>() && name == this->dragSlider) {
                                            auto [ min, max ] = setting->getRange();
                                            auto range = max - min;
                                            float newValue;

                                            newValue = min + ((mousePos._x - (sRect._x + 5.f)) / ((sRect._z - 7.f) - (sRect._x + 5.f))) * range;
                                            newValue = std::clamp(newValue, min, max);

                                            if(setting->isType<float>())
                                                *setting->get<float>() = newValue;
                                            else
                                                *setting->get<int>() = static_cast<int>(newValue);
                                        };
                                        
                                        currY += sSize.y + (window->pad / 2.f);
                                    };
                                };

                                currY += size.y + (mod == window->mods.back() ? 0.f : (window->pad / 2.f));
                            };

                        if(found)
                            this->isDraggingSlider = false;
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
                } else if(this->isDraggingSlider && (action == 1 && !isDown)) {
                    this->isDraggingSlider = false;
                };

                if(actionDone)
                    return;
                
                /* Do other potential actions */

                if((action == 1 || action == 2) && isDown) {
                    for(auto iter = windows.rbegin(); iter != windows.rend(); ++iter) {
                        auto& window = *iter;
                        auto titleSize = Renderer::getTextSize(std::string(window->getTitle() + "   "), window->fontSize);
                        auto titleRect = Vec4<float>(window->rectPos.x, window->rectPos.y, window->rectPos.z, window->rectPos.y + (titleSize.y));

                        if(titleRect.intersects(mousePos)) {
                            //
                        } else if(!window->isCollapsed) {
                            auto currY = (titleRect._w - 2.f) + (window->pad / 2.f);
                            for(auto& mod : window->mods) {
                                auto module = mod->mod;
                                auto size = Renderer::getTextSize(std::string(module->name + "   "), window->fontSize);
                                auto rect = Vec4(window->rectPos.x, currY, window->rectPos.z, (currY + size.y));

                                if(rect.intersects(mousePos)) {
                                    actionDone = true;
                                    if(action == 2) {
                                        mod->isCollapsed = !mod->isCollapsed;
                                    } else {
                                        module->toggleState();
                                    };
                                    return;
                                };

                                if(!mod->isCollapsed) {
                                    for(auto& [ name, setting ] : module->settings) {
                                        if(!setting->isVisible())
                                            continue;
                                        
                                        auto sSize = Renderer::getTextSize(name, window->fontSize);
                                        auto sRect = Vec4(window->rectPos.x, currY + (sSize.y + (window->pad / 2.f)), window->rectPos.z, ((currY + (sSize.y + (window->pad / 2.f))) + size.y));

                                        if(sRect.intersects(mousePos)) {
                                            actionDone = true;
                                            if(action == 2) {
                                                //
                                            } else {
                                                if(setting->isType<bool>()) {
                                                    auto v = setting->get<bool>();
                                                    *v = !*v;
                                                } else if(setting->isType<float>() || setting->isType<int>() && !this->isDraggingSlider) {
                                                    this->isDraggingSlider = true;
                                                    this->dragSlider = name;
                                                } else if(setting->isType<uint64_t>()) {
                                                    if(!this->interactingModKB) {
                                                        this->interactingModKB = module;
                                                    } else {
                                                        if(module == this->interactingModKB) {
                                                            this->interactingModKB = nullptr;
                                                        };
                                                    };
                                                };
                                            };
                                            return;
                                        };
                                        
                                        currY += sSize.y + (window->pad / 2.f);
                                    };
                                };

                                currY += size.y + (mod == window->mods.back() ? 0.f : (window->pad / 2.f));
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

                    if(isDown) {
                        if(key == VK_ESCAPE) {
                            if(this->interactingModKB) {
                                this->interactingModKB->setBind(0);
                                this->interactingModKB = nullptr;
                                return;
                            } else {
                                return this->toggleState();
                            };
                        };

                        if(this->interactingModKB) {
                            this->interactingModKB->setBind(key);
                            this->interactingModKB = nullptr;
                        };
                    };
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

                    windows.clear();
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
                        auto window = std::make_unique<ClickGuiWindow>(category);
                        totalWidth += (window->getBounds().x + space);
                    };

                    totalWidth -= space;
                    auto startX = (display.x - totalWidth) / 2.f;

                    auto currX = startX;
                    for(auto category : this->mgr->getCategories()) {
                        auto window = std::make_unique<ClickGuiWindow>(category);
                        
                        window->tPos = ImVec2(currX, 20.f);
                        currX += (window->getBounds().x + space);
                        window->fontSize = std::min(14.f * this->uiScale, 20.f);

                        for(auto module : category->getModules()) {
                            auto mod = std::make_unique<ClickGuiWindow::Mod>(module);

                            window->mods.push_back(std::move(mod));
                        };
                        
                        windows.push_back(std::move(window));
                    }
                };

                auto upMostWin = (ClickGuiWindow*)nullptr;
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

                auto hoveringTooltip = HoveringTooltip("", 0.f);
                for(auto& window : windows) {
                    
                    auto bounds = window->getBounds();
                    auto titleSize = Renderer::getTextSize(std::string(window->getTitle() + "   "), window->fontSize);
                    
                    window->rectPos.x = window->tPos.x; window->rectPos.y = window->tPos.y;
                    window->rectPos.z = window->tPos.x + bounds.x;

                    if(window->rectPos.w <= 0.f || this->dragWin == window.get())
                        window->rectPos.w = (window->isCollapsed ? window->tPos.y : window->tPos.y + bounds.y);

                    this->reachOff(&window->rectPos.w, window->isCollapsed ? window->tPos.y + titleSize.y : window->tPos.y + bounds.y, (window->mods.size() * 2.f));

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
                    for(auto& mod : window->mods) {
                        auto module = mod->mod;
                        auto size = Renderer::getTextSize(std::string(module->name + "   "), window->fontSize);
                        auto rect = Vec4(window->rectPos.x, currY, window->rectPos.z, (currY + size.y));

                        if(currY + (size.y) > window->rectPos.w)
                            break;

                        Renderer::drawText(
                            ImVec2(
                                window->tPos.x + 4.f, currY
                            ), module->name, window->fontSize, module->getState() ? ImColor(3.f, 252.f, 207.f) : ImColor(255.f, 255.f, 255.f)
                        );

                        {
                            auto text = (mod->isCollapsed ? "+ " : "- ");
                            Renderer::drawText(
                                ImVec2(
                                    window->rectPos.z - Renderer::getTextW(text, window->fontSize), currY
                                ), text, window->fontSize, ImColor(50.f, 140.f, 240.f)
                            );
                        }

                        if(upMostWin == window.get() && rect.intersects(mousePos) && module->description.length() > 0)
                            hoveringTooltip = HoveringTooltip(module->description, window->fontSize);

                        if(!mod->isCollapsed) {
                            for(auto& [ name, setting ] : module->settings) {
                                if(!setting->isVisible())
                                    continue;
                                
                                auto sSize = Renderer::getTextSize(name, window->fontSize);
                                auto sRect = Vec4(window->rectPos.x, currY + (sSize.y + (window->pad / 2.f)), window->rectPos.z, ((currY + (sSize.y + (window->pad / 2.f))) + size.y));

                                if((currY + (size.y + (window->pad / 2.f)) + (size.y)) > window->rectPos.w)
                                    break;
                                
                                auto key = name;

                                if(setting->isType<float>()) {
                                    std::stringstream ss;
                                    ss << std::fixed << std::setprecision(2) << *setting->get<float>();
                                    key += std::string(": " + ss.str());
                                } else if(setting->isType<int>()) {
                                    key += std::string(": " + std::to_string(*setting->get<int>()));
                                } else if(setting->isType<uint64_t>()) {
                                    std::string displayKey;

                                    BYTE keyboardState[256] = { 0 };
                                    if (GetKeyboardState(keyboardState)) {
                                        int scanCode = MapVirtualKey((unsigned int)module->bindKey, MAPVK_VK_TO_VSC);
                                        WCHAR result[2];
                                        int resultLength = ToUnicode((unsigned int)module->bindKey, scanCode, keyboardState, result, 2, 0);

                                        if(resultLength) {
                                            std::wstring wkeyStr(result, result + resultLength);
                                            for (auto& ch : wkeyStr)
                                                displayKey += std::toupper(ch);
                                        } else {
                                            displayKey = (vkToStringMap.find((unsigned int)module->bindKey) != vkToStringMap.end() ? vkToStringMap.at((unsigned int)module->bindKey) : "Err");
                                        }
                                    };

                                    key += std::string(": " + std::string(
                                        this->interactingModKB == module ? "..." : module->bindKey ? displayKey : "None"
                                    ));
                                };

                                auto textColor = ImColor(255.f, 255.f, 255.f);

                                Renderer::fillRect(
                                    ImVec4(
                                        sRect._x + 3.f, sRect._y - 4.f, (sRect._z - 3.f), std::min((window->rectPos.w - 4.f), sRect._w + 4.f)
                                    ),
                                ImColor(2.f, 43.f, 115.f, 1.f), 1.f);

                                if(setting->isType<bool>()) {
                                    auto v = setting->get<bool>();
                                    if(*v) {
                                        textColor = ImColor(66.f, 245.f, 164.f);
                                    };
                                    Renderer::fillRect(
                                        ImVec4(
                                            sRect._z - 6.f, sRect._y, sRect._z - 4.f, sRect._w
                                        ), *v ? textColor : ImColor(210.f, 10.f, 40.f), 1.f
                                    );
                                };

                                if(setting->isType<float>() || setting->isType<int>()) {
                                    float v = setting->isType<float>() ? *setting->get<float>() : static_cast<float>(*setting->get<int>());
                                    auto [min, max] = setting->getRange();

                                    float handlePos = (sRect._x + 5.f) + (v - min) / (max - min) * ((sRect._z - 5.f) - (sRect._x + 5.f));

                                    Renderer::fillRect(
                                        ImVec4(
                                            sRect._x + 5.f, sRect._w + 1.f, 
                                            handlePos, sRect._w + 3.f
                                        ), 
                                        ImColor(110.f, 30.f, 230.f, 1.f), 1.f
                                    );

                                    if (handlePos < sRect._z - 5.f) {
                                        Renderer::fillRect(
                                            ImVec4(
                                                handlePos, sRect._w + 1.f,
                                                sRect._z - 5.f, sRect._w + 3.f
                                            ), 
                                            ImColor(200.f, 200.f, 200.f, 1.f), 1.f
                                        );
                                    }
                                };
                                
                                Renderer::drawText(
                                    ImVec2(
                                        window->tPos.x + 6.f, (currY + (sSize.y + (window->pad / 2.f)) - 2.f)
                                    ), key, window->fontSize, textColor
                                );

                                currY += sSize.y + (window->pad / 2.f);
                            };
                        };

                        currY += size.y + (mod == window->mods.back() ? 0.f : (window->pad / 2.f));
                    };

                };

                if(hoveringTooltip.text.length() > 0) {
                    auto textSize = Renderer::getTextSize(hoveringTooltip.text, hoveringTooltip.fontSize);

                    auto hRect = ImVec4(
                        mousePos._x - (textSize.x / 2.f), (mousePos._y - 14.f) - (textSize.y / 2.f),
                        (mousePos._x - (textSize.x / 2.f)) + textSize.x, ((mousePos._y - 14.f) - (textSize.y / 2.f)) + textSize.y
                    );

                    Renderer::fillRect(hRect, ImColor(2.f, 43.f, 115.f, 1.f), 1.f);
                    Renderer::drawText(
                        ImVec2(hRect.x, hRect.y), hoveringTooltip.text, hoveringTooltip.fontSize, ImColor(255.f, 255.f, 255.f)
                    );
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