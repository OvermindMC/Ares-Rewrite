#pragma once

#include "Entity/Player.h"
#include "GuiData/GuiData.h"
#include "Minecraft/Minecraft.h"
#include "Input/ClientInputHandler.h"
#include "MinecraftGame/MinecraftGame.h"
#include "ScreenController/ScreenController.h"
#include "LoopbackPacketSender/LoopbackPacketSender.h"

class ClientInstance {
public:
    auto getLocalPlayer(void) -> Player*;
public:
    auto getPacketSender(void) -> LoopbackPacketSender*;
    auto getInputHandler(void) -> ClientInputHandler*;
    auto getLevelRenderer(void) -> LevelRenderer*;
    auto getMinecraftGame(void) -> MinecraftGame*;
    auto getMinecraft(void) -> Minecraft*;
    auto getGuiData(void) -> GuiData*;
public:
    auto grabMouse(void) -> void;
    auto releaseMouse(void) -> void;
public:
    auto getScreenName(void) -> std::string;
public:
    BUILD_ACCESS(Vec2<float>, mousePos, 0x498);
};