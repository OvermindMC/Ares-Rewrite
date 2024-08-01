#include "Actor.h"

Vec3 Actor::getPosition() const {
    if(auto* svc = this->ctx.tryGetComponent<StateVectorComponent>()) {
        return svc->oldPosition;
    };
    return Vec3();
};

bool Actor::isJumping() const {
    return this->ctx.hasComponent<FlagComponent<MobIsJumpingFlag>>();
};

bool Actor::isOnGround() const {
    return this->ctx.hasComponent<OnGroundFlagComponent>();
};

void Actor::setIsOnGround(bool state) {
    if(state && !this->isOnGround()) {
        this->ctx.addComponent<OnGroundFlagComponent>();
    } else if(!state && this->isOnGround()) {
        this->ctx.removeComponent<OnGroundFlagComponent>();
    };
};

float Actor::getSpeed() const {
    if(auto* msc = this->ctx.tryGetComponent<MovementSpeedComponent>()) {
        return msc->speed;
    };
    return 0.f;
};