#pragma once

#include "Actor.h"

class Player : public Actor {
private:
    virtual ~Player(void);
public:
    virtual auto knockback(class Actor*, int, float, float, float, float, float) -> void;
    virtual auto spawnAnim(void) -> void;
    virtual auto setSprinting(bool) -> void;
};