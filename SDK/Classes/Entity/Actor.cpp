#include "Actor.h"

auto Actor::getEntityCtx(void) -> EntityContext* {

    return (EntityContext*)((char*)(this) + 0x8);

};

auto Actor::getRuntimeID(void) -> unsigned long long {

    auto assure = this->getComponent<RuntimeIDComponent>();
    auto entityCtx = this->getEntityCtx();

    return assure && assure->contains(entityCtx->entityId) ? assure->get(entityCtx->entityId).runtimeId : NULL;

};

auto Actor::getEntityTypeId(void) -> unsigned char {

    using GetEntityTypeId = unsigned char (__thiscall*)(Actor*);
    static auto _GetEntityTypeId = (GetEntityTypeId)(Mem::findSig("E8 ? ? ? ? 83 F8 5F")->get(Signature::SearchType::Ref));

    return _GetEntityTypeId(this);

};

auto Actor::getPos(void) -> Vec3<float> {

    auto data = this->getComponentData<StateVectorComponent>();
    return (data ? data->position : Vec3<float>{});

};