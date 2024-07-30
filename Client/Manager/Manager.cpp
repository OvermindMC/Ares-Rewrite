#include "Manager.h"
#include "../Client.h"
#include "Modules/Category.h"

Manager::Manager(Client* client) : ciPtr(client) {
    this->initHooks();
    this->initCategories();
    this->initSubModules();

    for(auto& [ initType, result ] : this->initResults) {
        Debugger::log(
            std::string( initType == InitType::Hooks ? "Hooks" : initType == InitType::Categories ? "Categories" : initType == InitType::SubModules ? "Modules" : "" ) +
            " [ " + result.toString() + " ]"
        );
    };
};

Manager::~Manager() {
    if(this->hasInit(InitType::Hooks)) {
        MH_DisableHook(MH_ALL_HOOKS);
        MH_Uninitialize();
    };

    if(this->hasInit(InitType::Categories)) {
        this->categories.clear();
    };
};

void Manager::initHooks() {
    if(this->hasInit(InitType::Hooks))
        return;
    
    MH_STATUS res = MH_Initialize();

    if(res != MH_OK) {
        this->initResults.emplace(InitType::Hooks, Result(ResultStatus::ERR, "Failed to initialize MinHook"));
        return;
    };

    this->initResults.emplace(InitType::Hooks, Result(ResultStatus::OKAY, "Successfully initialized MinHook"));

    /*
        Emplace hooks, etc
    */
};

void Manager::initCategories() {
    if(!this->hasInit(InitType::Hooks)) {
        this->initResults.emplace(InitType::Categories, Result(ResultStatus::ERR, "Hooks were not initialized!"));
        return;
    };
    
    for(int i = 0; i < 6; i++) {
        auto type = static_cast<CategoryType>(i + 1);
        auto category = std::make_unique<Category>(this, type);
        this->categories.emplace(type, std::move(category));
    };

    this->initResults.emplace(InitType::Categories, Result(ResultStatus::OKAY, "Successfully initialized Categories"));
};

void Manager::initSubModules() {
    if(!this->hasInit(InitType::Categories)) {
        this->initResults.emplace(InitType::Categories, Result(ResultStatus::ERR, "Categories were not initialized!"));
        return;
    };
    
    this->initResults.emplace(InitType::SubModules, Result(ResultStatus::OKAY, "Successfully initialized Modules"));
};