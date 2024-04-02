#pragma once

#include "../Client.h"
#include "Event/Dispatcher.h"

/* Forward Declarations */
class Module;
class Category;
enum class CategoryType;

template<typename Type, typename... Args>
class Hook;

/* Manager Class */

class Manager {
/* Constructor, Deconstructor */

public:
    Manager(Client* client_raw_ptr);
    ~Manager(void);

/* Attributes for Runtime */
private:
    Client* client = nullptr;
    std::vector<void*> hooks;
    std::map<CategoryType, Category*> categories;

/* Attributes for Client Runtime */
private:
    std::map<uint64_t, bool> keymap;

/* Methods for Manager Runtime */
public:
    auto init(void) -> void;
public:
    auto initHooks(void) -> bool;
    auto initCategories(void) -> void;
    auto initSubModules(void) -> void;
public:
    auto getCategory(CategoryType category_type) -> Category*;
    auto getSortedEvents(void) -> std::map<EventType, std::vector<std::pair<EventDispatcher::EventPriority, void*>>>;
public:
    template<EventType event_type, typename... TArgs>
    auto dispatchEvent(TArgs... arguments) -> void {
        auto events = this->getSortedEvents();
        auto iter = events.find(event_type);

        if(iter != events.end()) {
            auto& list = iter->second;

            for(auto& event : list) {
                auto raw_event_ptr = static_cast<Event<TArgs...>*>(event.second);
                raw_event_ptr->callback(arguments...);
            };
        };
    };
};