#include "TestMod.h"

TestMod::TestMod(Manager* mgr) : Module(mgr, CategoryType::MISC, "Test Module", "For Developers") {

    this->setState(true);

    for(auto i = 0; i < 3; i++) {
        this->registerSetting<int>(std::to_string(i), &i);
    };

    this->registerEvent<EventType::Module_Toggle, EventDispatcher::EventPriority::Low>(
        std::function<void(void)>(
            [&](void) -> void {
                if(!this->getState())
                    return;
                
                auto instance = MC::getClientInstance();
                auto lp = instance ? instance->getLocalPlayer() : nullptr;

                if(!lp)
                    return;
            }
        )
    );

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