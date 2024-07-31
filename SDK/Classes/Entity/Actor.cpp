#include "Actor.h"

Vec3 Actor::getPosition() const {
    return this->getComponent<StateVectorComponent>()->position;
};

bool Actor::isJumping() const {
    return this->hasComponent<FlagComponent<MobIsJumpingFlag>>();
};

bool Actor::isOnGround() const {
    return this->hasComponent<OnGroundFlagComponent>();
};

void Actor::setIsOnGround(bool state) {
    if(state && !this->isOnGround()) {
        this->ctx.registry.emplace<OnGroundFlagComponent>(this->ctx.entityId);
    } else if(!state && this->isOnGround()) {
        this->removeComponent<OnGroundFlagComponent>();
    };
};