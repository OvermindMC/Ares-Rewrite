#include "Actor.h"

auto Actor::getEntityCtx(void) -> EntityContext* {

    return (EntityContext*)((char*)(this) + 0x8);

};

auto Actor::getRuntimeID(void) -> unsigned long long {

    auto assure = this->getComponent<RuntimeIDComponent>();
    auto entityCtx = this->getEntityCtx();

    return assure && assure->contains(entityCtx->entityId) ? assure->get(entityCtx->entityId).runtimeId : NULL;

};