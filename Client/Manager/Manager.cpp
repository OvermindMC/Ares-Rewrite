#include "Manager.h"
#include "../Client.h"
#include "Modules/Module/Module.h"

Manager::Manager(Client* client) : ciPtr(client) {
    this->initSigs();
    this->initHooks();
    this->initCategories();
    this->initSubModules();

    for(auto& [ initType, result ] : this->initResults) {
        Debugger::log(
            std::string( initType == InitType::Sigs ? "Sigs" : initType == InitType::Hooks ? "Hooks" : initType == InitType::Categories ? "Categories" : initType == InitType::SubModules ? "Modules" : "" ) +
            " [ " + result.toString() + " ]"
        );
    };

    this->ticking = true;

    while(this->ticking) {
        for(auto& [ type, category ] : this->categories) {
            for(auto module : category->getModules()) {
                module->baseTick();
            };
        };
        Sleep(1);
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

bool Manager::isTicking() const {
    return this->ticking;
};

void Manager::stop() {
    this->ticking = false;
};

void Manager::initSigs() {
    this->signatures = {
        {"Level_VTable", []() {
            auto sig = (uintptr_t)Mem::getSig("48 8D 05 ? ? ? ? 48 89 ? 48 8D 05 ? ? ? ? 48 89 ? 18 48 8D 05 ? ? ? ? 48 89 ? 20 ? ? ? ? ? ? ? 48 ? ? ? ? E8 ? ? ? ? 48 8B");
            auto offset = *(int*)(sig + 3);
            return (void**)(sig + offset + 7);
        }()},
        {"GameMode_VTable", []() {
            auto sig = (uintptr_t)Mem::getSig("48 8D 05 ? ? ? ? 48 8B D9 48 89 01 48 8B 89 ? ? ? ? 48 85 C9 74 11 48 8B 01 BA ? ? ? ? 48 8B 00 FF 15 ? ? ? ? 48 8B 8B ? ? ? ? 48 85 C9 74 17");
            auto offset = *(int*)(sig + 3);
            return (void**)(sig + offset + 7);
        }()}
    };

    bool problem = false;
    for(auto [ name, addr ] : this->signatures) {
        if(addr == nullptr) {
            Debugger::log("Signature failed at [" + name + "]");
            Sleep(2000);
            problem = true;
        }
    };

    this->initResults.emplace(InitType::Sigs, Result(problem ? ResultStatus::ERR : ResultStatus::OKAY, problem ? "Failed to resolve all Signatures" : "Successfully resolved all Signatures"));
};

#include "Hook/Hooks/Level/Level_Hook.h"
#include "Hook/Hooks/GameMode/GmTick_Hook.h"

void Manager::initHooks() {
    if(this->hasInit(InitType::Hooks))
        return;
    
    MH_STATUS res = MH_Initialize();

    if(res != MH_OK) {
        this->initResults.emplace(InitType::Hooks, Result(ResultStatus::ERR, "Failed to initialize MinHook"));
        return;
    };

    this->initResults.emplace(InitType::Hooks, Result(ResultStatus::OKAY, "Successfully initialized MinHook"));

    new Level_Hook(this);
    new GmTick_Hook(this);
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

#include "Modules/Module/Misc/TestModule.h"
#include "Modules/Module/Misc/Uninject.h"

void Manager::initSubModules() {
    if(!this->hasInit(InitType::Categories)) {
        this->initResults.emplace(InitType::Categories, Result(ResultStatus::ERR, "Categories were not initialized!"));
        return;
    };
    
    this->initResults.emplace(InitType::SubModules, Result(ResultStatus::OKAY, "Successfully initialized Modules"));

    new TestMod(this->getCategory<CategoryType::MISC>());
    new Uninject(this->getCategory<CategoryType::MISC>());
};