#include "Tick.h"

Actor_TickHook::Actor_TickHook(Manager* mgr) : Hook<void, Actor*>(mgr, "Actor_Tick", mgr->getSig<void**>("Actor_VTable")[29],
    [&](Actor* entity) -> void {
        
        auto typeId = entity->getEntityTypeId();
        auto runtimeId = entity->getRuntimeID();
        
        if(typeId == 63 || ( EntityUtils::isHostile(typeId) || EntityUtils::isPassive(typeId) )) {
            std::lock_guard<std::mutex> lock(entityMapMutex);
            auto& entityMap = this->mgr->entityMap;

            if(!entityMap.contains(runtimeId))
                entityMap.insert(std::pair<uint64_t, Actor*>(runtimeId, entity));
        };
        
        return this->_Func(entity);
    }
) {};