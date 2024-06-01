#include "TestMod.h"

TestMod::TestMod(Manager* mgr) : Module(mgr, CategoryType::MISC, "Test Module", "For Developers") {

    this->setState(true);

    this->registerEvent<EventType::Packet_SendToServer, EventDispatcher::EventPriority::Medium>(
        std::function<void(LoopbackPacketSender*, Packet*, bool*)>(
            [&](LoopbackPacketSender* pktSender, Packet* packet, bool* cancel) -> void {
                if(!this->getState())
                    return;
                
                auto id = packet->getId();
                
                //
            }
        )
    );

};