#pragma once

#include "../../Hook.h"

class SendToServer_Hook : public Hook<void, void*, void*> {
public:
    SendToServer_Hook(Manager*);
};