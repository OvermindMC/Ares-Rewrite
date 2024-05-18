#include "Player.h"

auto Player::getGameMode(void) -> GameMode* {

    return *(GameMode**)((uintptr_t)(this) + 0xEB0);

};

auto Player::getSupplies(void) -> PlayerInventory* {

    return *(PlayerInventory**)((uintptr_t)(this) + 0x788);

};