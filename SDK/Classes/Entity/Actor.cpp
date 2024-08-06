#include "Actor.h"

uint64_t Actor::getRuntimeId() const {
    if(auto* c = this->ctx.tryGetComponent<RuntimeIDComponent>()) {
        return c->runtimeId;
    };
    return 0;
};

uint8_t Actor::getEntityTypeId() const {
    static void* sig = Mem::getRef("E8 ? ? ? ? 83 F8 5F"); // 48 83 EC 38 8B 41 18 48 8D 54 24 20 48 8B 49 10 89 44 24 20 E8 17 8B 01 00 48
    using Func = uint8_t (__thiscall*)(const Actor*);
    Func func = (Func)sig;

    return func ? func(this) : 0;
};

bool Actor::isAlive() const {
    static void* sig = Mem::getSig("48 83 EC 28 80 B9 ? ? ? ? ? 75 10"); // vtable index[50] - 1.21.2
    using Func = bool (__thiscall*)(const Actor*);
    Func func = (Func)sig;

    return func ? func(this) : false;
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