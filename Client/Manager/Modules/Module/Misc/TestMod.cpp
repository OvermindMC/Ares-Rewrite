#include "TestModule.h"

TestMod::TestMod(Manager* mgr) : Module(mgr, CategoryType::MISC, "Test Module", "For Developers") {

    this->setState(true);

};