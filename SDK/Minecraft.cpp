#include "Minecraft.h"

auto MC::getClientInstance(void) -> ClientInstance* {

    static auto sig = Mem::findSig("48 89 0D ? ? ? ? 48 89 0D ? ? ? ? 48 85 C0 74 0F 48 8B C8 E8 ? ? ? ? 48 8B 0D ? ? ? ? 48 85 C9 74 09 48 83 C4 28 E9 ? ? ? ? 48 83 C4 28 C3 CC CC CC CC CC CC CC CC CC CC CC CC CC CC 48 83 EC 28 48 8D 0D ? ? ? ? FF 15 ? ? ? ? 48 8B 0D ? ? ? ? 48 85 C9 74 09 48 83 C4 28 E9 ? ? ? ? 48 83 C4 28 C3 CC CC CC CC CC 48 83 EC 28 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8D 0D ? ? ? ? 48 83 C4 28 E9 ? ? ? ? 40 53 48 83 EC 20 48 8B 0D ? ? ? ? 48 8B 59 08 80 7B 19 00 75 4E 48 89 7C 24 ? 0F 1F 40 00 4C 8B 43 10 48 8D 15 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8B FB 48 8B 1B 48 8D 4F 20");
    static auto clientinstance_raw_ptr = Mem::getNestedPtr((uintptr_t)sig->get(Signature::SearchType::VTable), { 0x0, 0x58, 0x0, 0x0 }, true);
    
    return (ClientInstance*)(clientinstance_raw_ptr);

};

auto MC::getEntities(void) -> std::vector<Actor*> {
    auto results = std::vector<Actor*>();
    
    auto instance = getClientInstance();
    auto lp = instance ? instance->getLocalPlayer() : nullptr;
    auto ctx = lp ? lp->getEntityCtx() : nullptr;

    if(lp && ctx) {
        auto& registry = ctx->registry;
        auto actorOwners = registry.view<ActorOwnerComponent>();

        for(auto ent : actorOwners) {
            if(!registry.valid(ent))
                continue;
            auto& ref = actorOwners.get<ActorOwnerComponent>(ent);
            auto actor = ref.actor;

            if(actor && actor->isAlive())
                results.push_back(actor);
        };
    };
    
    return results;
};

auto EntityUtils::isHostile(unsigned char type) -> bool {

    static const std::unordered_set<unsigned char> hostileEntities {
        32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 52,
        53, 54, 55, 57, 58, 59, 104, 105, 110, 114, 116, 123, 124, 126, 127, 131
    };
    return hostileEntities.find(type) != hostileEntities.end();

};

auto EntityUtils::isPassive(unsigned char type) -> bool {

    static const std::unordered_set<unsigned char> passiveEntities {
        10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29,
        30, 31, 74, 75, 108, 109, 111, 112, 113, 115, 118, 121, 122, 125, 128, 132, 133, 134
    };
    return passiveEntities.find(type) != passiveEntities.end();

};