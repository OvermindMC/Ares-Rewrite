#include "Manager.h"
#include "Modules/Module/Module.h"

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

            /*static int c = 0;

            if(c > 50) {
                Debugger::log("Bye");
                
                Sleep(1000);
                this->client->stop();
            };

            c++;*/

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

auto Manager::assignModule(Module* module_raw_ptr, CategoryType category_type) -> void {

    auto category = (this->categories.contains(category_type) ? this->categories.at(category_type) : nullptr);

    if(category) {

        category->addModule(module_raw_ptr);

    };

};

auto Manager::getCategory(CategoryType category_type) -> Category* {

    return (this->categories.contains(category_type) ? this->categories.at(category_type) : nullptr);

};