#pragma once

#include "Event.h"
#include "../../../Utils/Utils.h"

class EventDispatcher {
public:
    enum class EventPriority : int {
        Low = 1, Medium = 2, Highest = 3
    };
public:
    template<typename... TArgs>
    auto registerEvent(EventType event_type, EventDispatcher::EventPriority event_priority, std::function<void(TArgs...)> callback_func) -> void {
        this->events_map[event_type].emplace_back(event_priority, new Event<TArgs...>(callback_func));
    };
public:
    auto unregisterEvent(EventType event_type) -> void {
        auto iter = this->events_map.find(event_type);

        if(iter != this->events_map.end()) {
            auto& list = iter->second;
            
            for(auto& event : list) {
                auto raw_event_ptr = static_cast<Event<>*>(event.second);
                delete raw_event_ptr;
            };

            events_map.erase(iter->first);

        };
    };
public:
    template<typename... TArgs>
    auto dispatchEvent(EventType event_type, TArgs... arguments) -> void {
        auto iter = this->events_map.find(event_type);

        if(iter != this->events_map.end()) {
            auto& list = iter->second;

            std::sort(list.begin(), list.end(), [](const auto& a, const auto& b) {
                return a.first > b.first;
            });

            for(auto& event : list) {
                auto raw_event_ptr = static_cast<Event<TArgs...>*>(event.second);
                raw_event_ptr->callback(arguments...);
            };
        };
    };
public:
    ~EventDispatcher(void) {
        for(auto& event : this->events_map) {
            for(auto item : event.second) {
                auto raw_event_ptr = static_cast<Event<>*>(item.second);
                if(raw_event_ptr)
                    delete raw_event_ptr;
            };
            this->events_map[event.first].clear();
        };
        this->events_map.clear();
    };
public:
    std::map<EventType, std::vector<std::pair<EventDispatcher::EventPriority, void*>>> events_map;
};