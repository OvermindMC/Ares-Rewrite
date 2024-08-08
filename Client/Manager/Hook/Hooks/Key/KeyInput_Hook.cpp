#include "KeyInput_Hook.h"
#include "../../../Modules/Module/Module.h"

KeyInput_Hook::KeyInput_Hook(Manager* mgr) : Hook<void, uint64_t, bool>(mgr, "KeyInput_Hook", mgr->getSig<void*>("KeyInput_Func"),
    [&](uint64_t key, bool isDown) -> void {
        if(this->mgr->keyMap.contains(key)) {
            this->mgr->keyMap.at(key) = isDown;
        } else {
            this->mgr->keyMap.emplace(key, isDown);
        };

        bool cancelEv = false;
        this->mgr->dispatchEvent<EventType::OnKey>(key, isDown, &cancelEv);

        if(isDown) {
            for(auto category : this->mgr->getCategories()) {
                for(auto module : category->getModules()) {
                    if(key == module->getBind()) {
                        module->setIsEnabled(!module->isEnabled());
                    };
                };
            };
        };
        
        if(!cancelEv)
            return this->_Func(key, isDown);
    }
) {};