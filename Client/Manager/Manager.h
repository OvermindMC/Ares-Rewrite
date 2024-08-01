#pragma once

#include "../Client.h"
#include "Event/Dispatcher.h"

class Category;
enum class CategoryType;

class Manager {
public:
    Manager(Client*);
    ~Manager();

    enum class InitType { Sigs, Hooks, Categories, SubModules };
    bool hasInit(InitType type) const { return this->initResults.contains(type) ? this->initResults.at(type) == ResultStatus::OKAY : false; };

    bool isTicking() const;
    void stop();
    
    void initSigs();
    void initHooks();
    void initCategories();
    void initSubModules();

    template<CategoryType type>
    Category* getCategory() { return categories.contains(type) ? categories.at(type).get() : nullptr; };

    template<typename T>
    T getSig(std::string query) { return signatures.contains(query) ? (T)signatures.at(query) : T{}; };

    std::vector<std::pair<EventDispatcher::EventPriority, std::unique_ptr<BaseEvent>>> getSortedEvents(EventType filterType) const;

    template<EventType type, typename... Args>
    void dispatchEvent(Args&&... args) {
        auto sortedEvents = this->getSortedEvents(type);

        for (const auto& [priority, eventPtr] : sortedEvents) {
            auto* event = dynamic_cast<Event<Args...>*>(eventPtr.get());

            if (event && event->callback) {
                event->callback(std::forward<Args>(args)...);
            };
        };
    };
private:
    bool ticking = false;
    Client* ciPtr = nullptr;
    std::map<InitType, Result> initResults;
    std::map<std::string, void*> signatures;
    std::map<CategoryType, std::unique_ptr<Category>> categories;
};