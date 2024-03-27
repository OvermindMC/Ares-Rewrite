#include "Client.h"
#include "Manager/Manager.h"

auto Client::getName(void) -> std::string {

    return this->name;

};

auto Client::getVersion(void) -> Version {

    return this->version;

};

auto Client::init(void) -> void {

    if(this->isRunning)
        return;
    
    this->mgr = new Manager(this); /* Create new Manager instance */

};