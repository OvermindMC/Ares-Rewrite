#pragma once

#include "../Category.h"

class Module {
public:
    Module(Category*, const std::string&);
    virtual ~Module();

    PTR_ACCESS(Category*, category, cPtr);
    PTR_ACCESS(EventDispatcher*, evDispatcher, evDis);

    Manager* getMgr() const;

    bool isEnabled() const;
    void setIsEnabled(bool);
    std::string getName() const;

private:
    Category* cPtr = nullptr;
    EventDispatcher* evDis;
    
    const std::string name;
    std::pair<bool, bool> state = {false, false};
};