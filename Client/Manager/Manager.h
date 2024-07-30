#pragma once

#include "../Client.h"

class Manager {
public:
    Manager(Client*);
    ~Manager();

    enum class InitType { Hooks, Categories, SubModules };
    bool hasInit(InitType type) const;

    void initHooks();
    void initCategories();
    void initSubModules();
private:
    Client* ciPtr = nullptr;
    std::map<InitType, Result> initResults;
};