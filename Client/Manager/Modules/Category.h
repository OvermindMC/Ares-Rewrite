#pragma once

#include "../Manager.h"

class Module;

enum class CategoryType { COMBAT = 1, MOVE = 2, RENDER = 3, WORLD = 4, PLAYER = 5, MISC = 6 };
class Category {
public:
    Category(Manager*, CategoryType);
    ~Category();

    void registerModule(Module*);
    CategoryType getType() const;
    std::vector<Module*> getModules() const;

    PTR_ACCESS(Manager*, mgr, miPtr);
private:
    Manager* miPtr = nullptr;
    
    CategoryType cType;
    std::vector<Module*> modules;
};