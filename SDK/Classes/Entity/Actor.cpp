#include "Actor.h"

EntityContext* Actor::getEntityCtx() const {
    return (EntityContext*)((char*)(this) + 0x8);
};