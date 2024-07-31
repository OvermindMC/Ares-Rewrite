#include "Uninject.h"

Uninject::Uninject(Category* c) : Module(c, "Uninject") {
    this->setIsEnabled(false);
};