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
    Category* category;
public:
    std::string name, description;
    uint64_t bindKey = 0x0;

/* Methods for Runtime */
public:
    //
};