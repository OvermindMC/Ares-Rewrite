#include "KeyInput.h"

KeyInput_Hook::KeyInput_Hook(Manager* mgr) : Hook<void, unsigned long long, bool>(mgr, "Input_Key", mgr->getSig<void*>("KeyInput"),
    [&](unsigned long long key, bool isDown) -> void {
        
        this->mgr->dispatchEvent<EventType::KeyInput, uint64_t, bool>(key, isDown);
        return this->_Func(key, isDown);

    }
) {};