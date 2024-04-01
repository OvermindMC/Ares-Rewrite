#include "Client.h"
#include "Manager/Manager.h"

Client::Client(const char* client_name) : name(client_name ? client_name : "Client") {};

Client::~Client() {

    delete this->mgr;

};

auto Client::getName(void) -> std::string {

    return this->name;

};

auto Client::getVersion(void) -> Version {

    return this->version;

};

auto Client::init(void) -> void {

    if(this->_isRunning)
        return;
    
    this->_isRunning = true;
    
    Debugger::init(this->name);
    Debugger::log("Initialized Client <" + this->name + ">");
    
    this->mgr = new Manager(this); /* Create new Manager instance */
    this->mgr->init();

};

auto Client::isRunning(void) -> bool {

    return this->_isRunning;

};