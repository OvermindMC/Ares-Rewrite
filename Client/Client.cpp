#include "Client.h"

auto Client::getName(void) -> std::string {

    return this->name;

};

auto Client::getVersion(void) -> Version {

    return this->version;

};