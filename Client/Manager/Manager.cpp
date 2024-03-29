#include "Manager.h"

Manager::Manager(Client* client_raw_ptr) : client(client_raw_ptr) {};

Manager::~Manager(void) {

    //

};

auto Manager::init(void) -> void {

    Debugger::log("Initialized Manager");

    std::ostringstream o;
    o << std::hex << this->client;

    Debugger::log(o.str());

};