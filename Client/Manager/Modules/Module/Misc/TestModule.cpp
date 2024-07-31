#include "TestModule.h"

TestMod::TestMod(Category* c) : Module(c, "Test Module") {
    this->setIsEnabled(true);
};

void TestMod::onTick() {
    auto instance = MC::getClientInstance();
    auto lp = instance->getPlayer();

    if(!lp)
        return;
};

void TestMod::onEnable(){
    Debugger::log(this->getName() + " Enabled!");

    Player* lp = MC::getClientInstance()->getPlayer();

    if(!lp)
        return;
    
    Debugger::log(lp->getPosition().toStr());
};

void TestMod::onDisable() {
    Debugger::log(this->getName() + " Disabled!");
};