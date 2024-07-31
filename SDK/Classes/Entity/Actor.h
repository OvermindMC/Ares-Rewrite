#pragma once

#include "EntityContext.h"
#include "Component/Components.h"

class Actor {
private:
    virtual ~Actor();
public:
    EntityContext ctx;

    template<typename T>
    T* getComponent() const {
        return ctx.registry.try_get<T>(ctx.entityId);
    };

    template<typename T>
    bool hasComponent() const {
        return ctx.registry.any_of<T>(ctx.entityId);
    };

    template<typename... T>
    void removeComponent() const {
        (void)std::initializer_list<int>{
            (ctx.registry.any_of<T>(ctx.entityId) ? (ctx.registry.remove<T>(ctx.entityId), 0) : 0)...
        };
    };

    Vec3 getPosition() const;
    
    bool isJumping() const;
    
    bool isOnGround() const;
    void setIsOnGround(bool);
};