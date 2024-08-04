#include "Player.h"

void Player::setSprinting(bool state) {
    static void* sig = Mem::getSig("48 89 5C 24 ? 57 48 83 EC 20 48 8B 01 0F B6 DA BA ? ? ? ?"); // vtable index[153] - 1.21.2
    using Func = void (__thiscall*)(Player*, bool);
    Func func = (Func)sig;

    if(func)
        func(this, state);
};