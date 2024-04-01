#include "Manager.h"
#include "Modules/Category.h"

Manager::Manager(Client* client_raw_ptr) : client(client_raw_ptr) {};

Manager::~Manager(void) {

    if(!this->hooks.empty()) {
        
        //

    };

    MH_DisableHook(MH_ALL_HOOKS);
    MH_Uninitialize();

    for(auto& item : this->categories) {
        delete item.second;
    };

    this->categories.clear();

};

auto Manager::init(void) -> void {

    Debugger::log("Initialized Manager");

    if(this->initHooks()) {
        this->initCategories();
        this->initSubModules();

        while(this->client->isRunning()) {

            //

            Sleep(1);

        };
    };

};

auto Manager::initHooks(void) -> bool {

    if(MH_Initialize() != MH_OK)
        return false;
    
    // WIP

    return true;

};

auto Manager::initCategories(void) -> void {

    for(auto i = static_cast<int>(CategoryType::COMBAT); i <= static_cast<int>(CategoryType::MISC); i++) {
        
        auto type = static_cast<CategoryType>(i);
        
        if(!this->categories.contains(type)) {
            this->categories[type] = new Category(this, type);
            Debugger::log(
                std::string("Initializing Category <" + this->categories[type]->getName() + ">")
            );
        };

    };

};

auto Manager::initSubModules(void) -> void {

    //

};