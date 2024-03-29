#pragma once

#include "../../../Mem/Mem.h"

struct EntityContext {
    void* mRegistry;
    entt::basic_registry<EntityId>& registry;
    EntityId entityId;
};