#pragma once

#include "../../Hook.h"

class SendToServer_Hook : public Hook<void, LoopbackPacketSender*, Packet*> {
public:
    SendToServer_Hook(Manager*);
};