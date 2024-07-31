#pragma once

#include "../Category.h"

class Module {
public:
    Module(Category*, const std::string&);
    virtual ~Module();

    PTR_ACCESS(Category*, category, cPtr);

    Manager* getMgr() const;

    bool isEnabled() const;
    void setIsEnabled(bool);
    std::string getName() const;

    void baseTick();
    virtual void onTick() {};
    virtual void onEnable() {};
    virtual void onDisable() {};

private:
    Category* cPtr = nullptr;
    
    const std::string name;
    std::pair<bool, bool> state = {false, false};
};