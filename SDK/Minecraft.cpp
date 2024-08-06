#include "Minecraft.h"

ClientInstance* MC::getClientInstance() {
    static uintptr_t ref = (uintptr_t)Mem::getRef("E8 ? ? ? ? 90 48 8B 40 10 48 8B 18 48 8B 03 48 8B 78 20", 0x55);
    
    static int relOff = *(int*)(ref + 3);
    static uintptr_t baseOffset = (uintptr_t)(uintptr_t**)(ref + relOff + 7);

    static auto ptr = Mem::resPtr(baseOffset, { 0x0, 0x58, 0x0, 0x0 });
    return ptr ? (ClientInstance*)ptr : nullptr;
};

Player* MC::getLocalPlayer() {
    ClientInstance* ci = getClientInstance();
    return ci ? ci->getPlayer() : nullptr;
};

std::vector<Actor*> MC::getEntities() {
    std::vector<Actor*> results;

    if (auto player = getLocalPlayer()) {
        if (auto ctx = &player->ctx) {
            auto& registry = ctx->enttRegistry;

            for (auto ent : registry.view<ActorOwnerComponent>()) {
                if (registry.valid(ent)) {
                    auto& ownerComponent = registry.get<ActorOwnerComponent>(ent);
                    if (auto actor = ownerComponent.actor) {
                        results.push_back(actor);
                    };
                };
            };
        };
    };

    return results;
};