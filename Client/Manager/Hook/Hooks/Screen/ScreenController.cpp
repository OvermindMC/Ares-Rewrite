#include "ScreenController.h"

ScreenController_TickHook::ScreenController_TickHook(Manager* mgr) : Hook<void, ScreenController*>(mgr,"ScreenController_Tick",  mgr->getSig<void**>("ScreenController_VTable")[2],
    [&](ScreenController* screen_controller) -> void {
        
        // WIP
        
        return this->_Func(screen_controller);

    }
) {};