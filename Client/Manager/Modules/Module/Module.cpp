#include "Module.h"

Module::Module(Manager* manager_raw_ptr, CategoryType category_type, std::string module_name, std::string module_description, uint64_t module_bind) : name(module_name), description(module_description), bindKey(module_bind) {

    this->category = manager_raw_ptr->getCategory(category_type);
    this->category->addModule(this);

};

Module::~Module(void) {

    //

};