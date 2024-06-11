#include "ModuleList.h"

class ModDisplacement {
public:
    Module* mod = nullptr;

    std::string displayText;
    float xOff = 0.f;
    ImVec4 rect;

    ModDisplacement(Module* module) : mod(module) {
        this->updateDisplayText();
    };

    auto updateDisplayText(void) -> void {
        if(!this->mod)
            return;
        
        auto text = this->mod->name;
        
        std::vector<std::pair<std::string, Setting*>> btns;
        for(auto& [ name, setting ] : this->mod->settings) {
            if(setting->isType<bool>()) {
                auto state = setting->get<bool>();

                if(!*state)
                    continue;
                
                btns.emplace_back(name, setting.get());
            };
        };

        for(auto& [name, setting] : btns) {
            text += ((setting == btns.front().second ? " | " : "") + (name + (setting == btns.back().second ? "" : ", ")));
        };

        displayText = text;
    };
};

ModuleList::ModuleList(Manager* mgr) : Module(mgr, CategoryType::RENDER, "ModuleList", "Render Enabled Modules") {

    this->setState(true);
    
    static auto displacements = std::vector<std::unique_ptr<ModDisplacement>>();

    this->registerEvent<EventType::Present_Resize, EventDispatcher::EventPriority::Highest>(
        std::function<void(void)>(
            [&](void) -> void {
                auto instance = MC::getClientInstance();
                auto guidata = instance ? instance->getGuiData() : nullptr;

                if(guidata->uiScale != this->uiScale) {
                    this->uiScale = guidata->uiScale;
                    this->fontSize = std::min(14.f * this->uiScale, 20.f);
                };

                auto displaySize = ImGui::GetIO().DisplaySize;

                for(auto& displacement : displacements) {
                    displacement->updateDisplayText();

                    auto text = displacement->displayText;
                    auto size = Renderer::getTextSize(text, this->fontSize);
                    displacement->xOff = (displacement->mod->getState()) ? (displaySize.x - size.x) - this->pad.x : displaySize.x;
                };
            }
        )
    );
    
    this->registerEvent<EventType::Present_Tick, EventDispatcher::EventPriority::Highest>(
        std::function<void(void)>(
            [&](void) -> void {
                if(!this->getState())
                    return;
                
                if(displacements.empty()) {
                    for(auto category : this->mgr->getCategories()) {
                        for(auto module : category->getModules()) {
                            displacements.push_back(std::make_unique<ModDisplacement>(module));
                        };
                    };
                };
                
                std::sort(displacements.begin(), displacements.end(), [&](std::unique_ptr<ModDisplacement>& a, std::unique_ptr<ModDisplacement>& b) {
                    return Renderer::getTextW(a->displayText, this->fontSize) > Renderer::getTextW(b->displayText, this->fontSize);
                });

                for(auto& displacement : displacements)
                    displacement->updateDisplayText();

                auto displaySize = ImGui::GetIO().DisplaySize;
                auto currY = 0.f;

                for (size_t currIndex = 0; currIndex < displacements.size(); ++currIndex) {
                    auto &displacement = displacements[currIndex];

                    auto text = displacement->displayText;
                    auto size = Renderer::getTextSize(text, this->fontSize);

                    if(displacement->xOff <= 0.f) {
                        displacement->xOff = displaySize.x; //(displacement->mod->getState()) ? (displaySize.x - size.x) - this->pad.x : displaySize.x;
                    };

                    float targetXOff = (displacement->mod->getState()) ? (displaySize.x - size.x) - this->pad.x : displaySize.x;

                    ModuleList::reachOff(&displacement->xOff, targetXOff, 4.f);

                    if (displacement->xOff >= (displaySize.x - this->pad.x))
                        continue;

                    displacement->rect = ImVec4(
                        displacement->xOff - this->pad.x,
                        currY,
                        displaySize.x,
                        currY + ((size.y * 2.f) + this->pad.y)
                    );

                    Renderer::fillRect(
                        displacement->rect, ImColor(0.f, 27.f, 74.f, .8f), 0.f
                    );

                    Renderer::fillRect(
                        ImVec4(
                            displacement->rect.x,
                            displacement->rect.y,
                            displacement->rect.x + 1.5f,
                            displacement->rect.w
                        ), ImColor(255.f, 255.f, 255.f), 1.f
                    );

                    size_t nextIndex = currIndex + 1;
                    while (nextIndex < displacements.size()) {
                        auto& next = displacements[nextIndex];
                        if (!next->mod->getState()) {
                            ++nextIndex;
                            continue;
                        }
                        if (next->xOff < displaySize.x) {
                            break;
                        };
                        ++nextIndex;
                    };

                    if (nextIndex < displacements.size() || displacement == displacements.back()) {
                        auto &next = (nextIndex < displacements.size() ? displacements[nextIndex] : displacements.back());
                        Renderer::fillRect(
                            ImVec4(
                                displacement->rect.x,
                                displacement->rect.w,
                                next->rect.x + 2.f,
                                displacement->rect.w
                            ), ImColor(255.f, 255.f, 255.f), 1.f
                        );
                    };

                    Renderer::drawText(
                        ImVec2(
                            displacement->rect.x + this->pad.x,
                            displacement->rect.y + this->pad.y + ((displacement->rect.w - displacement->rect.y - size.y) / 2.f)
                        ), text, this->fontSize, ImColor(255.f, 255.f, 255.f)
                    );

                    currY += ((size.y * 2.f) + this->pad.y);
                };
            }
        )
    );

    this->registerEvent<EventType::MouseInput, EventDispatcher::EventPriority::Medium>(
        std::function<void(char, bool, Vec2<float>, bool*)>(
            [&](char action, bool isDown, Vec2<float> mousePos, bool* cancel) -> void {
                if(action == 2 && isDown) {
                    auto instance = MC::getClientInstance();
                    auto mcMousePos = instance ? instance->mousePos : Vec2<float>();

                    for(auto& displacement : displacements) {
                        if(!displacement->mod->getState())
                            continue;
                        
                        if(Vec4<float>(displacement->rect.x, displacement->rect.y, displacement->rect.z, displacement->rect.w).intersects(mcMousePos)) {
                            displacement->mod->toggleState();
                            break;
                        };
                    };
                };
            }
        )
    );

};

auto ModuleList::reachOff(float* x, float xOff, float modifier) -> void {

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