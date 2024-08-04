#pragma once

#include "Actor.h"
#include "../GameMode.h"

class Player : public Actor {
private:
    virtual ~Player();
public:
    void swing();
    void setSprinting(bool);
    void displayClientMsg(std::string);

    GameMode* getGameMode();
};