#include "Category.h"
#include "Module/Module.h"

Category::Category(Manager* manager_raw_ptr, CategoryType category_type) : mgr(manager_raw_ptr), type(category_type) {

    //

};

Category::~Category(void) {

    for(auto module : this->modules) {
        delete module;
    };

    this->modules.clear();

};

auto Category::getType(void) -> CategoryType {

    return this->type;

};

auto Category::getName(void) -> std::string {

    auto result = std::string("");

    switch(this->type) {
        case CategoryType::COMBAT:
            result = "Combat";
        break;
        case CategoryType::MOVE:
            result = "Movement";
        break;
        case CategoryType::RENDER:
            result = "Render";
        break;
        case CategoryType::WORLD:
            result = "World";
        break;
        case CategoryType::PLAYER:
            result = "Player";
        break;
        case CategoryType::MISC:
            result = "Misc";
        break;
    };

    return result;

};

auto Category::getModules(void) -> std::vector<Module*> {

    return this->modules;

};

auto Category::addModule(Module* module_raw_ptr) -> bool {

    auto iter = std::find(this->modules.begin(), this->modules.end(), module_raw_ptr);

    if(iter != this->modules.end())
        return false;
    
    this->modules.push_back(module_raw_ptr);
    return true;

};