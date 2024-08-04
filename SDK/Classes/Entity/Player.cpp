#include "Player.h"

void Player::setSprinting(bool state) {
    static void* sig = Mem::getSig("48 89 5C 24 ? 57 48 83 EC 20 48 8B 01 0F B6 DA BA ? ? ? ?"); // vtable index[153] - 1.21.2
    using Func = void (__thiscall*)(Player*, bool);
    Func func = (Func)sig;

    if(func)
        func(this, state);
};

void Player::displayClientMsg(std::string message) {
    static void* sig = Mem::getSig("48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC 40 48 8B F2 48 8B 89 ? ? ? ?"); // vtable index[213] - 1.21.2
    using Func = void (__thiscall*)(Player*, std::string*);
    Func func = (Func)sig;

    if(func)
        func(this, &message);
};