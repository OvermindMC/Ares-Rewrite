#include "../Actor.h"
#include "../EntityContext.h"
#include "../../../../Utils/Debugger/Debugger.h"

auto Level::getEntityContextList(void) -> std::vector<EntityContext*> {

    return **(std::vector<EntityContext*>**)((uintptr_t)(this) + 0x1B78);

};

auto Level::getRuntimeIds(void) -> std::vector<uint64_t> {
    auto results = std::vector<uint64_t>();

    {
        static auto sig = Mem::findSig("E8 ? ? ? ? BA 70 27 BA F0")->get(Signature::SearchType::Ref);

        using AssureT = entt::basic_storage<RuntimeIDComponent, EntityId>* (__fastcall*)(entt::basic_registry<EntityId>&, entt::id_type);
        auto assureF = (AssureT)(sig);

        auto type = entt::type_id<RuntimeIDComponent>();
        auto list = this->getEntityContextList();

        for(auto it = list.begin(); it < list.end();) {
            void* mRegistry = *it;
            entt::basic_registry<EntityId>* registry = (entt::basic_registry<EntityId>*)list.at(std::distance(list.begin(), it + 1));
            EntityId entityId = (EntityId&)list.at(std::distance(list.begin(), it + 2));

            auto assure = assureF(*registry, type.hash());
            auto runtimeId = assure->contains(entityId) ? assure->get(entityId).runtimeId : 0;

            if(runtimeId)
                results.push_back(runtimeId);

            it += 4;
        };
    };

    return results;
};

auto Level::getUniqueIds(void) -> std::vector<uint64_t> {
    auto results = std::vector<uint64_t>();

    {
        static auto sig = Mem::findSig("E8 ? ? ? ? BA 70 27 BA F0")->get(Signature::SearchType::Ref);

        using AssureT = entt::basic_storage<ActorUniqueIDComponent, EntityId>* (__fastcall*)(entt::basic_registry<EntityId>&, entt::id_type);
        auto assureF = (AssureT)(sig);

        auto type = entt::type_id<ActorUniqueIDComponent>();
        auto list = this->getEntityContextList();

        for(auto it = list.begin(); it < list.end();) {
            void* mRegistry = *it;
            entt::basic_registry<EntityId>* registry = (entt::basic_registry<EntityId>*)list.at(std::distance(list.begin(), it + 1));
            EntityId entityId = (EntityId&)list.at(std::distance(list.begin(), it + 2));

            auto assure = assureF(*registry, type.hash());
            auto uniqueID = assure->contains(entityId) ? assure->get(entityId).uniqueId : 0;

            if(uniqueID)
                results.push_back(uniqueID);

            it += 4;
        };
    };

    return results;
};

auto Level::getEntities(void) -> std::vector<Actor*> {
    auto results = std::vector<Actor*>();

    for(auto runtimeId : this->getUniqueIds()) {
        auto entity = Mem::callVFunc<52, Actor*, uint64_t, bool>(this, runtimeId, false);

        if(entity)
            results.push_back(entity);
    };

    return results;
};