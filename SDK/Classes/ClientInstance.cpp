#include "ClientInstance.h"

auto ClientInstance::getLocalPlayer(void) -> Player* {

    return Mem::callVFunc<29, Player*>(this);

};

auto ClientInstance::getGuiData(void) -> GuiData* {

    return *(GuiData**)((uintptr_t)(this) + 0x558);

};

auto ClientInstance::grabMouse(void) -> void {

    return Mem::callVFunc<331, void>(this);

};

auto ClientInstance::releaseMouse(void) -> void {

    return Mem::callVFunc<332, void>(this);

};