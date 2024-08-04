#pragma once

#include "EntityContext.h"
#include "Component/Components.h"

#include "../Level/Level.h"

class Actor {
private:
    virtual ~Actor();
public:
    EntityContext ctx;

    Vec3 getPosition() const;
    void setPosition(Vec3);
    
    bool isJumping() const;
    
    bool isOnGround() const;
    void setIsOnGround(bool);

    float getSpeed() const;

    Vec3 getMotion() const;
    void setMotion(Vec3);
    void lerpMotion(Vec3, float);
};