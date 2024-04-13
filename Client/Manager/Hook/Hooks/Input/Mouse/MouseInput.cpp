#include "MouseInput.h"

MouseInput_Hook::MouseInput_Hook(Manager* mgr) : Hook<void, void*, char, bool, short, short, short, short, bool>(mgr, "Input_Mouse", mgr->getSig<void*>("MouseInput"),
    [&](void* p1, char action, bool isDown, short x, short y, short deltaX, short deltaY, bool isScroll) -> void {
        
        this->mgr->dispatchEvent<EventType::MouseInput, uint64_t, bool>(action, isDown, Vec2<float>(x, y));
        return this->_Func(p1, action, isDown, x, y, deltaX, deltaY, isScroll);

    }
) {};