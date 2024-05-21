#include "MouseInput.h"

MouseInput_Hook::MouseInput_Hook(Manager* mgr) : Hook<void, void*, char, bool, short, short, short, short, bool>(mgr, "Input_Mouse", mgr->getSig<void*>("MouseInput"),
    [&](void* p1, char action, bool isDown, short x, short y, short deltaX, short deltaY, bool isScroll) -> void {
        
        this->mgr->dispatchEvent<EventType::MouseInput, char, bool, Vec2<float>>(action, isDown, Vec2<float>(x, y));

        if(ImGui::GetCurrentContext()) {
            auto& io = ImGui::GetIO();
            auto instance = MC::getClientInstance();

            if(instance) {
                auto mousePos = ImVec2(instance->mousePos._x, instance->mousePos._y);

                io.MousePos = mousePos;
                io.MousePosPrev = mousePos;

                if(action > 0 && action < 3) {
                    io.MouseDown[0] = isDown;
                    io.AddMouseButtonEvent(action, isDown);
                };

                //io.AddMousePosEvent(mousePos.x, mousePos.y);
            };
        };

        return this->_Func(p1, action, isDown, x, y, deltaX, deltaY, isScroll);

    }
) {};