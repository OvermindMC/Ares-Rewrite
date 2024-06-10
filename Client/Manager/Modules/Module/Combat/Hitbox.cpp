#include "Hitbox.h"

Hitbox::Hitbox(Manager* mgr) : Module(mgr, CategoryType::COMBAT, "Hitbox", "Modify entity shadow radius") {

    this->registerSetting("Width", &this->radius._x, 0.6f, 4.f);
    this->registerSetting("Height", &this->radius._y, 1.8f, 4.f);

    this->registerEvent<EventType::Level_Tick, EventDispatcher::EventPriority::Medium>(
        std::function<void(Level*)>(
            [&](Level* level) -> void {
                if(!this->getState())
                    return;
                
                auto instance = MC::getClientInstance();
                auto entities = MC::getEntities();

                if(entities.empty())
                    return;
                
                auto lp = instance ? instance->getLocalPlayer() : nullptr;
                auto myRuntimeId = lp ? lp->getRuntimeID() : 0;

                if(!lp || !myRuntimeId)
                    return;
                
                for(auto entity : entities) {
                    if(!entity || !entity->isAlive() || entity->getRuntimeID() == myRuntimeId)
                        continue;
                    
                    auto typeId = entity->getEntityTypeId();
                    auto aabbData = entity->getComponentData<AABBShapeComponent>();

                    if(!aabbData)
                        continue;
                    
                    if(this->cached.contains(typeId)) {
                        aabbData->radius = this->radius;
                    } else {
                        this->cached.emplace(typeId, aabbData->radius);
                    };
                };
            }
        )
    );

    this->registerEvent<EventType::Module_Toggle, EventDispatcher::EventPriority::Medium>(
        std::function<void(void)>(
            [&](void) -> void {
                if(this->getState())
                    return;
                
                auto instance = MC::getClientInstance();
                auto entities = MC::getEntities();

                if(entities.empty())
                    return;
                
                auto lp = instance ? instance->getLocalPlayer() : nullptr;
                auto myRuntimeId = lp ? lp->getRuntimeID() : 0;

                if(!lp || !myRuntimeId)
                    return;
                
                for(auto entity : entities) {
                    if(!entity || !entity->isAlive() || entity->getRuntimeID() == myRuntimeId)
                        continue;
                    
                    auto typeId = entity->getEntityTypeId();
                    auto aabbData = entity->getComponentData<AABBShapeComponent>();

                    if(!aabbData)
                        continue;
                    
                    if(this->cached.contains(typeId)) {
                        aabbData->radius = this->cached.at(typeId);
                    };
                };
            }
        )
    );

};