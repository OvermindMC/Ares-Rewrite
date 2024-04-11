#include "Tick.h"
#include "../Tick.h"

Level_TickHook::Level_TickHook(Manager* mgr) : Hook<void, Level*>(mgr, "Level_Tick", mgr->getSig<void**>("Level_VTable")[99],
    [&](Level* level) -> void {
        
        std::lock_guard<std::mutex> lock(entityMapMutex);
        auto& entityMap = this->mgr->entityMap;

        for(auto iter = entityMap.begin(); iter != entityMap.end();) {
            auto [ runtimeId, entity ] = *iter;
            if(!entity || !entity->isAlive()) {
                iter = entityMap.erase(iter);
            } else {
                ++iter;
            };
        };

        this->mgr->dispatchEvent<EventType::Level_Tick, Level*>(level);
        return this->_Func(level);

    }
) {};