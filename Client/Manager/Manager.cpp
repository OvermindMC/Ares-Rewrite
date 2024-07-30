#include "Manager.h"
#include "../Client.h"

Manager::Manager(Client* client) : ciPtr(client) {
    this->initHooks();
    this->initCategories();
    this->initSubModules();
};

Manager::~Manager() {
    if(this->hasInit(InitType::Hooks)) {
        MH_DisableHook(MH_ALL_HOOKS);
        MH_Uninitialize();
    };
};

bool Manager::hasInit(InitType type) const {
    return this->initResults.contains(type) ? this->initResults.at(type) == ResultStatus::OKAY : false;
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
    //
};

void Manager::initSubModules() {
    //
};