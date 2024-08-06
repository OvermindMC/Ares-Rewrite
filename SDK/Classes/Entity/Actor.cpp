#include "Actor.h"

uint64_t Actor::getRuntimeId() const {
    if(auto* c = this->ctx.tryGetComponent<RuntimeIDComponent>()) {
        return c->runtimeId;
    };
    return 0;
};

bool Actor::isAlive() const {
    static void* sig = Mem::getSig("48 83 EC 28 80 B9 ? ? ? ? ? 75 10"); // vtable index[50] - 1.21.2
    using Func = bool (__thiscall*)(Actor*);
    Func func = (Func)sig;

    return func ? func(const_cast<Actor*>(this)) : false;
};

Vec3 Actor::getPosition() const {
    if(auto* svc = this->ctx.tryGetComponent<StateVectorComponent>()) {
        return svc->oldPosition;
    };
    return Vec3();
};

void Actor::setPosition(Vec3 position) {
    this->ctx.addComponent<ActorSetPositionRequestComponent>(std::move(position));
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

Vec3 Actor::getMotion() const {
    if(auto* svc = this->ctx.tryGetComponent<StateVectorComponent>()) {
        return svc->positionDelta;
    };
    return Vec3();
};

void Actor::setMotion(Vec3 motion) {
    if(auto* svc = this->ctx.tryGetComponent<StateVectorComponent>()) {
        svc->positionDelta = motion;
    };
};

void Actor::lerpMotion(Vec3 motion, float t) {
    if(auto* svc = this->ctx.tryGetComponent<StateVectorComponent>()) {
        Vec3 currMotion = svc->positionDelta;
        svc->positionDelta = currMotion.lerp(motion, t);
    };
};