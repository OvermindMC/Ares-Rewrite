#include "ClientInstance.h"

auto ClientInstance::getLocalPlayer(void) -> Player* {

    return Mem::callVFunc<29, Player*>(this);

};

auto ClientInstance::getPacketSender(void) -> LoopbackPacketSender* {

    return *(LoopbackPacketSender**)((uintptr_t)(this) + 0xF0);

};

auto ClientInstance::getInputHandler(void) -> ClientInputHandler* {

    return *(ClientInputHandler**)((uintptr_t)(this) + 0x110);

};

auto ClientInstance::getLevelRenderer(void) -> LevelRenderer* {

    return *(LevelRenderer**)((uintptr_t)(this) + 0xE0);

};

auto ClientInstance::getMinecraftGame(void) -> MinecraftGame* {

    return *(MinecraftGame**)((uintptr_t)(this) + 0xB0);

};

auto ClientInstance::getMinecraft(void) -> Minecraft* {

    return *(Minecraft**)((uintptr_t)(this) + 0xD0);

};

auto ClientInstance::getGuiData(void) -> GuiData* {

    return *(GuiData**)((uintptr_t)(this) + 0x558);

};

auto ClientInstance::grabMouse(void) -> void {

    return Mem::callVFunc<331, void>(this);

};

auto ClientInstance::releaseMouse(void) -> void {

    return Mem::callVFunc<332, void>(this);

};

auto ClientInstance::getScreenName(void) -> std::string {

    static std::string out;
    Mem::callVFunc<147, void, std::string*>(this, &out);

    return out;

};