#include "Uninject.h"

Uninject::Uninject(Category* c) : Module(c, "Uninject") {
    this->setIsEnabled(false);
};

void Uninject::onEnable() {
    this->getMgr()->stop();
};