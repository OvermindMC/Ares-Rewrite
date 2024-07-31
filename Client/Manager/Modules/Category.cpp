#include "Category.h"
#include "Module/Module.h"

Category::Category(Manager* mgr, CategoryType type) : miPtr(mgr), cType(type) {
    //
};

Category::~Category() {
    for(auto module : this->modules) {
        delete module;
    };

    this->modules.clear();
};

void Category::registerModule(Module* module) {
    auto it = std::find(this->modules.begin(), this->modules.end(), module);

    if(it != this->modules.end())
        return;
    
    this->modules.push_back(module);
};

CategoryType Category::getType() const {
    return this->cType;
};

std::vector<Module*> Category::getModules() const {
    return this->modules;
};