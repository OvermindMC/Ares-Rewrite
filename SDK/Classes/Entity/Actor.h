#pragma once

#include "EntityContext.h"
#include "Component/Component.h"

class Actor {
public:
    auto getEntityCtx(void) -> EntityContext*;
public:
    template<typename T>
    auto getComponent(void) -> entt::basic_storage<T, EntityId>* {
        static auto sig = Mem::findSig("E8 ? ? ? ? BA 70 27 BA F0")->get(Signature::SearchType::Ref);

        if (!sig)
            return nullptr;

        using AssureT = entt::basic_storage<T, EntityId>* (__fastcall*)(entt::basic_registry<EntityId>&, entt::id_type);
        auto assureF = (AssureT)(sig);

        auto type = entt::type_id<T>();
        auto ctx = this->getEntityCtx();

        return assureF(ctx->registry, type.hash());
    };
public:
    auto getRuntimeID(void) -> unsigned long long;
private:
    virtual ~Actor(void);
};