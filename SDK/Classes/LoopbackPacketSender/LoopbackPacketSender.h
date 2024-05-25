#pragma once

#include "Packet/Text/TextPacket.h"

class LoopbackPacketSender {
public:
    auto send(Packet* packet) -> void {
        return Mem::callVFunc<1, void, Packet*>(this, packet);
    };
    auto sendToServer(Packet* packet) -> void {
        return Mem::callVFunc<2, void, Packet*>(this, packet);
    };
};