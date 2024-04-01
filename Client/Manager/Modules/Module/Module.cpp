#include "Module.h"

Module::Module(Manager* manager_raw_ptr, CategoryType category_type, std::string module_name, std::string module_description, uint64_t module_bind) : name(module_name), description(module_description), bindKey(module_bind) {

    this->category = manager_raw_ptr->getCategory(category_type);
    this->category->addModule(this);

};

Module::~Module(void) {

    //

};

auto Module::baseTick(void) -> void {

    if(this->state.first != this->state.second) {

        this->state.second = this->state.first;

        if(this->state.first) {
            //
        } else {
            //
        };

    };

};

auto Module::getState(void) -> bool {

    return this->state.first;

};

auto Module::toggleState(void) -> void {

    this->state.first = !this->state.first;

};

auto Module::setState(bool module_state) -> void {

    this->state.first = module_state;

};

auto Module::getBind(void) -> uint64_t {

    return this->bindKey;

};

auto Module::setBind(uint64_t module_bind) -> void {

    this->bindKey = module_bind;

};