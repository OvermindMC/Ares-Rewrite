#include "SendToServer.h"

SendToServer_Hook::SendToServer_Hook(Manager* mgr) : Hook<void, LoopbackPacketSender*, Packet*>(mgr, "SendToServer", mgr->getSig<void**>("LoopbackPacketSender_VTable")[2],
    [&](LoopbackPacketSender* _this, Packet* packet) -> void {
        
        bool cancel = false;

        this->mgr->dispatchEvent<EventType::Packet_SendToServer, LoopbackPacketSender*, Packet*, bool*>(_this, packet, &cancel);

        if(!cancel)
            return this->_Func(_this, packet);

    }
) {};