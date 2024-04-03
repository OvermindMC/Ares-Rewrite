#pragma once

#include "../Category.h"

/* Module Class */
class Module {
/* Constructor, Deconstructor */

public:
    Module(Manager* manager_raw_ptr, CategoryType category_type, std::string module_name, std::string module_description = "", uint64_t module_bind = 0x0);
    ~Module(void);

/* Attributes for Module */
private:
    Category* category_raw_ptr = nullptr;
    std::pair<bool, bool> state;
private:
    EventDispatcher* event_dispatcher_raw_ptr = nullptr;
public:
    std::string name, description;
    uint64_t bindKey = 0x0;
public:
    PTR_ACCESS(Category*, category, category_raw_ptr);
    PTR_ACCESS(Manager*, mgr, category_raw_ptr->mgr);
    PTR_ACCESS(Client*, client, mgr->client);
/* Methods for Runtime */
public:
    auto baseTick(void) -> void;
public:
    auto getState(void) -> bool;
    auto toggleState(void) -> void;
    auto setState(bool module_state) -> void;
public:
    auto getBind(void) -> uint64_t;
    auto setBind(uint64_t module_bind) -> void;
public:
    auto getEventDispatcher(void) -> EventDispatcher*;
};