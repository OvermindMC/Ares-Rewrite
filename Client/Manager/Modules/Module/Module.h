#pragma once

#include "../Category.h"

class Module {
public:
    Module(Category*, const std::string&);
    virtual ~Module() = default;

    PTR_ACCESS(Category*, category, cPtr);

    Manager* getMgr() const;
    EventDispatcher* getEventDispatcher() const;

    bool isEnabled() const;
    void setIsEnabled(bool);
    std::string getName() const;

    template<EventType type, typename... Args>
    void registerEvent(EventDispatcher::EventPriority priority, std::function<void(Args...)> fCallback) {
        this->evDis->registerEvent<type>(priority, fCallback);
    };

    template<EventType type>
    void registerEvent(EventDispatcher::EventPriority priority, std::function<void()> fCallback) {
        this->evDis->registerEvent<type>(priority, fCallback);
    };

    template<EventType type>
    void unregisterEvent() {
        this->evDis->unregisterEvent(type);
    };

private:
    Category* cPtr = nullptr;
    std::unique_ptr<EventDispatcher> evDis;
    
    const std::string name;
    std::pair<bool, bool> state = {false, false};
};