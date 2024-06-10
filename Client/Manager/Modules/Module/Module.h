#pragma once

#include "../Category.h"

class Setting {
public:
    Setting(std::variant<float*, bool*, uint64_t*, int*> value, float min = 0.0f, float max = 0.0f, bool* visible = nullptr) : _item(value), _min(min), _max(max), dependantBool(visible) {};

    template<typename T>
    auto isType(void) -> bool {
        return std::holds_alternative<T*>(_item);
    };

    template<typename T>
    auto get(void) -> T* {
        if(auto ptr = std::get<T*>(this->_item)) {
            return ptr ? ptr : nullptr;
        };
        return nullptr;
    };

    auto getRange(void) -> std::pair<float, float> {
        return std::pair<float, float>(this->_min, this->_max);
    };

    auto isVisible(void) -> bool {
        return this->dependantBool ? *this->dependantBool : true;
    };
private:
    std::variant<float*, bool*, uint64_t*, int*> _item;
    
    float _min, _max;
    bool* dependantBool = nullptr;
};

/* Module Class */
class Module {
/* Constructor, Deconstructor */

public:
    Module(Manager* manager_raw_ptr, CategoryType category_type, std::string module_name, std::string module_description = "", uint64_t module_bind = 0x0);
    ~Module(void);

/* Attributes for Module */
private:
    Category* category_raw_ptr = nullptr;
    std::unique_ptr<EventDispatcher> event_dispatcher_ptr = nullptr;
public:
    std::vector<std::pair<std::string, std::unique_ptr<Setting>>> settings;
    std::string name, description;
    std::pair<bool, bool> state;
    uint64_t bindKey = 0x0;
    
    PTR_ACCESS(Category*, category, category_raw_ptr);
    PTR_ACCESS(Manager*, mgr, category_raw_ptr->mgr);
    PTR_ACCESS(Client*, client, mgr->client);
/* Methods for Runtime */

    auto baseTick(void) -> void;
    
    auto getState(void) -> bool;
    auto toggleState(void) -> void;
    auto setState(bool module_state) -> void;
    
    auto getBind(void) -> uint64_t;
    auto setBind(uint64_t module_bind) -> void;
    
    auto getEventDispatcher(void) -> EventDispatcher*;
    
    template<EventType type, EventDispatcher::EventPriority priority, typename... Args>
    auto registerEvent(std::function<void(Args...)> callback) -> void {
        this->getEventDispatcher()->registerEvent<Args...>(type, priority, callback);
    };
    
    template<EventType type>
    auto unregisterEvent(void) -> void {
        this->getEventDispatcher()->unregisterEvent(type);
    };

    template<typename T>
    auto registerSetting(std::string name, T* value, T min = 0, T max = 0, bool* visibility = nullptr) -> std::enable_if_t<
        std::is_same_v<T, float> || std::is_same_v<T, bool> || std::is_same_v<T, uint64_t> || std::is_same_v<T, int>, void> {
        settings.push_back(
            std::make_pair(name, std::make_unique<Setting>(value, static_cast<float>(min), static_cast<float>(max), visibility))
        );
    };
};