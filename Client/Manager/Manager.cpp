#include "Manager.h"

Manager::Manager(Client* client_raw_ptr) : client(client_raw_ptr) {};

Manager::~Manager(void) {

    //

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

    //

};

auto Manager::initSubModules(void) -> void {

    //

};