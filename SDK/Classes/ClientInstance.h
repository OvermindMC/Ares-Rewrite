#pragma once

#include "Entity/Player.h"
#include "GuiData/GuiData.h"
#include "MinecraftGame/MinecraftGame.h"

class ClientInstance {
public:
    auto getLocalPlayer(void) -> Player*;
public:
    auto getLevelRenderer(void) -> LevelRenderer*;
    auto getMinecraftGame(void) -> MinecraftGame*;
    auto getGuiData(void) -> GuiData*;
public:
    auto grabMouse(void) -> void;
    auto releaseMouse(void) -> void;
public:
    auto getScreenName(void) -> std::string;
public:
    BUILD_ACCESS(Vec2<float>, mousePos, 0x498);
};