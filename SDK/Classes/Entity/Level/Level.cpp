#include "../Actor.h"
#include "../EntityContext.h"

template<typename T>
auto Level::getEntityComponents(void) -> std::vector<T*> {
    auto results = std::vector<T*>();

    static auto sig = Mem::findSig("E8 ? ? ? ? BA 70 27 BA F0")->get(Signature::SearchType::Ref);

    using AssureT = entt::basic_storage<T, EntityId>* (__fastcall*)(entt::basic_registry<EntityId>&, entt::id_type);
    auto assureF = (AssureT)(sig);

    auto type = entt::type_id<T>();
    auto list = **(std::vector<EntityContext*>**)((uintptr_t)(this) + 0x1B78);

    for(auto it = list.begin(); it < list.end();) {
        void* mRegistry = *it;
        entt::basic_registry<EntityId>* registry = (entt::basic_registry<EntityId>*)list.at(std::distance(list.begin(), it + 1));
        EntityId entityId = (EntityId&)list.at(std::distance(list.begin(), it + 2));

        auto assure = assureF(*registry, type.hash());

        if(assure && assure->contains(entityId))
            results.push_back((T*)std::addressof(assure->get(entityId)));

        it += 4;
    };

    return results;
};

auto Level::getRuntimeIds(void) -> std::vector<uint64_t> {
    auto results = std::vector<uint64_t>();

    for(auto component : this->getEntityComponents<RuntimeIDComponent>())
        results.push_back(component->runtimeId);

    return results;
};

auto Level::getUniqueIds(void) -> std::vector<uint64_t> {
    auto results = std::vector<uint64_t>();

    for(auto component : this->getEntityComponents<ActorUniqueIDComponent>())
        results.push_back(component->uniqueId);

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