#include "Hitbox.h"

Hitbox::Hitbox(Category* c) : Module(c, "Hitbox") {
    this->setIsEnabled(true);

    this->registerEvent<EventType::OnLevel, Level*>(
        EventDispatcher::EventPriority::Medium,
        [&](Level* level) {
            if(!this->isEnabled())
                return;
            
            Player* player = MC::getLocalPlayer();

            if(!player)
                return;
            
            uint64_t lRuntimeId = player->getRuntimeId();
            auto entities = MC::getEntities();

            if(entities.size() <= 1)
                return;
            
            for(auto ent : entities) {
                if(ent->getRuntimeId() == lRuntimeId)
                    continue;
                
                uint8_t typeId = ent->getEntityTypeId();
                auto shapeAABB = ent->ctx.tryGetComponent<AABBShapeComponent>();

                if(!typeId || !shapeAABB)
                    continue;
                
                if(this->cached.contains(typeId)) {
                    shapeAABB->radius = this->radius;
                } else {
                    this->cached.emplace(typeId, shapeAABB->radius);
                };
            };
        }
    );

    this->registerEvent<EventType::OnDisable>(
        EventDispatcher::EventPriority::Low,
        [&]() {
            Player* player = MC::getLocalPlayer();

            if(!player)
                return;
            
            uint64_t lRuntimeId = player->getRuntimeId();
            auto entities = MC::getEntities();

            for(auto ent : entities) {
                if(ent->getRuntimeId() == lRuntimeId)
                    continue;
                
                uint8_t typeId = ent->getEntityTypeId();
                auto shapeAABB = ent->ctx.tryGetComponent<AABBShapeComponent>();

                if(this->cached.contains(typeId)) {
                    shapeAABB->radius = this->cached.at(typeId);
                };
            }
        }
    );
};