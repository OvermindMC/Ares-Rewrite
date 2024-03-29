#include "ClientInstance.h"

auto ClientInstance::getLocalPlayer(void) -> Player* {

    return Mem::callVFunc<29, Player*>(this);

};