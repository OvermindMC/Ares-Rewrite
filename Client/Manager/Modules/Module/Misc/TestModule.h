#pragma once

#include "../Module.h"

class TestMod : public Module {
public:
    TestMod(Category*);

    void onTick() override;
    void onEnable()  override;
    void onDisable()  override;
};