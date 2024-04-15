#pragma once

#include "../../../Mem/Mem.h"

class ScreenController {
public:
    auto getName(void) -> std::string;
public:
    auto closeScreen(void) -> void;
public:
    auto handleDropItem(std::string container, int slot) -> void;
    auto handleAutoPlace(std::string container, int slot) -> void;
};