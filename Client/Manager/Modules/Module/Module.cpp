#include "Module.h"

Module::Module(Category* category, const std::string& display_name) : cPtr(category), name(display_name) {
    category->registerModule(this);
};

Module::~Module() {
    //
};

Manager* Module::getMgr() const {
    return this->category ? this->category->mgr : nullptr;
};

bool Module::isEnabled() const {
    return this->state.second;
};

void Module::setIsEnabled(bool state) {
    this->state.first = state;
};

std::string Module::getName() const {
    return this->name;
};

void Module::baseTick() {
    if(this->state.first != this->state.second) {
        this->state.second = this->state.first;

        if(this->state.first) {
            this->onEnable();
        } else {
            this->onDisable();
        };
    };

    if(this->state.first) {
        this->onTick();
    };
};