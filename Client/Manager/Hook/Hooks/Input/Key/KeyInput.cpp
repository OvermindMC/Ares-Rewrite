#include "KeyInput.h"
#include "../../../../Modules/Module/Module.h"

KeyInput_Hook::KeyInput_Hook(Manager* mgr) : Hook<void, unsigned long long, bool>(mgr, "Input_Key", mgr->getSig<void*>("KeyInput"),
    [&](unsigned long long key, bool isDown) -> void {

        this->mgr->keymap.emplace(key, isDown);

        auto instance = MC::getClientInstance();
        auto canUseKeys = ( instance ? instance->getLocalPlayer() ? instance->getScreenName().rfind("hud_screen") != std::string::npos : false : true );

        if(canUseKeys && isDown) {
            for(auto category : this->mgr->getCategories()) {
                for(auto module : category->getModules()) {
                    if(module->bindKey == key)
                        module->toggleState();
                };
            };
        };

        bool cancel = false;
        
        this->mgr->dispatchEvent<EventType::KeyInput, uint64_t, bool, bool*>(key, isDown, &cancel);
        
        if(!cancel)
            return this->_Func(key, isDown);

    }
) {};