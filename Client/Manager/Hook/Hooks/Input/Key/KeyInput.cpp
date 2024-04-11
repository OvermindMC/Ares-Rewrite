#include "KeyInput.h"

KeyInput_Hook::KeyInput_Hook(Manager* mgr) : Hook<void, unsigned long long, bool>(mgr, "Input_Key", mgr->getSig<void*>("KeyInput"),
    [&](unsigned long long key, bool isDown) -> void {
        
        Debugger::log(std::string("Key was ") + std::string(isDown ? "pressed!" : "unpressed!"));
        
        return this->_Func(key, isDown);

    }
) {};