#include "SendToServer.h"

SendToServer_Hook::SendToServer_Hook(Manager* mgr) : Hook<void, void*, void*>(mgr, "SendToServer", mgr->getSig<void**>("LoopbackPacketSender_VTable")[2],
    [&](void* _this, void* packet) -> void {
        
        //this->mgr->dispatchEvent<EventType::ScreenControllerTick, ScreenController*>(screen_controller);

        return this->_Func(_this, packet);

    }
) {};