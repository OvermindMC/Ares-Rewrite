#pragma once

#include "EntityContext.h"
#include "Component/Components.h"

class Actor {
public:
    EntityContext* getEntityCtx() const;

    template<typename T>
    entt::basic_storage<T, EntityId>* getComponent() const {
        EntityContext* ctx = this->getEntityCtx();
        if (!ctx) {
            return nullptr;
        };

        auto& registry = ctx->registry;
        auto& storage = registry.storage<T>();
        
        return &storage;
    };
};