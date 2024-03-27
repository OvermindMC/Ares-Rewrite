#pragma once

#include "../Client.h"

/* Forward Declarations */
class Category;
enum class CategoryType;

template<typename Type, typename... Args>
class Hook;

class Manager {
/* Constructor, Deconstructor */

public:
    Manager(Client* client_raw_ptr) : client(client_raw_ptr) {};
    ~Manager(void) {};

/* Attributes for Runtime */
private:
    Client* client = nullptr;
    std::vector<void*> hooks;
    std::map<CategoryType, Category*> categories;

/* Attributes for Client Runtime */
private:
    std::map<uint64_t, bool> keymap;
};