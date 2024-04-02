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
    EventDispatcher* eventDispatcher = nullptr;
private:
    Category* category = nullptr;
    std::pair<bool, bool> state;
public:
    std::string name, description;
    uint64_t bindKey = 0x0;

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