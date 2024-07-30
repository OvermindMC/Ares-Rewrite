#include "Client.h"
#include "Manager/Manager.h"

Client::Client(const std::string& client_name, const Version& client_version) : clientName(client_name), clientVer(client_version) {
    Debugger::init(client_name);
    Debugger::log("Initialized Debugger");

    this->miPtr = new Manager(this);
};

Client::~Client() {
    SAFE_DEL(this->miPtr);
    Debugger::free();
};

std::string Client::getName() const {
    return this->clientName;
};

Version Client::getVer() const {
    return this->clientVer;
};