#include "TestModule.h"

TestMod::TestMod(Category* c) : Module(c, "Test Module") {
    this->setIsEnabled(true);
};

void TestMod::onTick() {
    //
};

void TestMod::onEnable(){
    Debugger::log(this->getName() + " Enabled!");
};

void TestMod::onDisable() {
    Debugger::log(this->getName() + " Disabled!");
};