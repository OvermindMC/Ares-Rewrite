#pragma once

#include "../Mem/Mem.h"
#include "../Utils/Utils.h"

class Client {
public:
    Client(const char* client_name) : name(client_name ? client_name : "") {}
    ~Client(void) {};
public:
    auto getName(void) -> std::string_view;
private:
    std::string_view name;
};