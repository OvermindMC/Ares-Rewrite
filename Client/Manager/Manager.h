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
    Client* client_instance_raw_ptr = nullptr;
private:
    std::vector<void*> hooks;
    std::map<uint64_t, bool> keymap;
    std::map<std::string, void*> signature_map;
    std::map<CategoryType, std::unique_ptr<Category>> categories;
public:
    PTR_ACCESS(Client*, client, client_instance_raw_ptr);
public:
    std::map<uint64_t, Actor*> entityMap;
/* Methods for Manager Runtime */
public:
    auto init(void) -> void;
    auto cleanupHooks(void) -> void;
public:
    auto initHooks(void) -> bool;
    auto initCategories(void) -> void;
    auto initSubModules(void) -> void;
public:
    template<typename T>
    auto getSig(std::string query) -> T {
        return (this->signature_map.contains(query) ? (T)this->signature_map.at(query) : T{});
    };
public:
    auto registerHook(void* hook_raw_ptr) -> bool;
    auto getHookRaw(std::string) -> void*;
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