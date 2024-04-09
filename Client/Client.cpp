#include "Client.h"
#include "Manager/Manager.h"

Client::Client(const char* client_name) : name(client_name ? client_name : "Client") {};

Client::~Client() {

    delete this->mgr_raw_ptr;

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
    
    this->mgr_raw_ptr = new Manager(this); /* Create new Manager instance */
    this->mgr_raw_ptr->init();

};

auto Client::isRunning(void) -> bool {

    return this->_isRunning;

};

auto Client::stop(void) -> void {

    this->_isRunning = false;

};