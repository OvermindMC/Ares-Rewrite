#pragma once

#include "../Client.h"

class Category;
enum class CategoryType;

class Manager {
public:
    Manager(Client*);
    ~Manager();

    enum class InitType { Hooks, Categories, SubModules };
    bool hasInit(InitType type) const { return this->initResults.contains(type) ? this->initResults.at(type) == ResultStatus::OKAY : false; };

    void initHooks();
    void initCategories();
    void initSubModules();

    template<CategoryType type>
    Category* getCategory() { return categories.contains(type) ? categories.at(type).get() : nullptr; };
private:
    Client* ciPtr = nullptr;
    std::map<InitType, Result> initResults;
    std::map<CategoryType, std::unique_ptr<Category>> categories;
};