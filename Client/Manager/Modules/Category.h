#pragma once

#include "../Manager.h"

/* Forward Declarations */
class Module;

/* Category Type */
enum class CategoryType {
    COMBAT = 1, MOVE = 2, RENDER = 3, WORLD = 4, PLAYER = 5, MISC = 6
};

/* Category Class */
class Category {
/* Constructor, Deconstructor */
public:
    Category(Manager* manager_raw_ptr, CategoryType category_type);
    ~Category(void);
/* Attributes for Category */
private:
    Manager* mgr_raw_ptr = nullptr;
    std::vector<Module*> modules;
    CategoryType type;
public:
    PTR_ACCESS(Manager*, mgr, mgr_raw_ptr);
    PTR_ACCESS(Client*, client, mgr->client);
/* Methods for Runtime */
public:
    auto getType(void) -> CategoryType;
    auto getName(void) -> std::string;
public:
    auto getModules(void) -> std::vector<Module*>;
    auto addModule(Module* module_raw_ptr) -> bool;
};