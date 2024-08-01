#pragma once

#include "Types.h"

template<typename... Args>
class Event {
public:
    std::function<void(Args...)> callback;
    Event(std::function<void(Args...)> fn) : callback(fn) {};
};

class EventDispatcher {
public:
    enum class EventPriority { Low, Medium, High };

    template<EventType type, typename... Args>
    void registerEvent(EventPriority priority, std::function<void(Args...)> fCallback) {
        this->events_map[type].emplace_back(priority, new Event<Args...>(fCallback));
    };
    
    template<EventType type>
    void registerEvent(EventPriority priority, std::function<void()> fCallback) {
        this->events_map[type].emplace_back(priority, new Event<>(fCallback));
    };
    
    void unregisterEvent(EventType type) {
        auto iter = this->events_map.find(type);

        if(iter != this->events_map.end()) {
            auto& list = iter->second;

            for(auto& event : list) {
                if(event.second) {
                    delete static_cast<Event<>*>(event.second);
                    event.second = nullptr;
                };
            };

            events_map.erase(iter->first);
        };
    };

    template<EventType type, typename... Args>
    void dispatchEvent(Args&&... args) {
        auto iter = this->events_map.find(type);

        if(iter != this->events_map.end()) {
            auto& list = iter->second;

            std::sort(list.begin(), list.end(), [](const auto& a, const auto& b) {
                return a.first > b.first;
            });

            for(auto& event : list) {
                if(event.second) {
                    static_cast<Event<Args...>*>(event.second)->callback(args...);
                };
            };
        };
    };

    std::map<EventType, std::vector<std::pair<EventDispatcher::EventPriority, void*>>> getEvents() const {
        return this->events_map;
    };

    ~EventDispatcher(void) {
        for(auto& event : this->events_map) {
            this->unregisterEvent(event.first);
        };
    };
private:
    std::map<EventType, std::vector<std::pair<EventDispatcher::EventPriority, void*>>> events_map;
};