#pragma once

#include "Types.h"

class BaseEvent {
public:
    virtual ~BaseEvent() = default;
    virtual void invoke(void* args) const = 0;
    virtual std::unique_ptr<BaseEvent> clone() const = 0;
};

template<typename... Args>
class Event : public BaseEvent {
public:
    std::function<void(Args...)> callback;

    Event(std::function<void(Args...)> fn) : callback(std::move(fn)) {}

    void invoke(void* args) const override {
        call(std::index_sequence_for<Args...>{}, args);
    };

    std::unique_ptr<BaseEvent> clone() const override {
        return std::make_unique<Event<Args...>>(*this);
    };
private:
    template<std::size_t... Is>
    void call(std::index_sequence<Is...>, void* args) const {
        callback(std::get<Is>(*reinterpret_cast<std::tuple<Args...>*>(args))...);
    };
};

class EventDispatcher {
public:
    enum class EventPriority { Low, Medium, High };

    template<EventType type, typename... Args>
    void registerEvent(EventPriority priority, std::function<void(Args...)> fCallback) {
        events_map[type].emplace_back(priority, std::make_unique<Event<Args...>>(std::move(fCallback)));
    };

    template<EventType type>
    void registerEvent(EventPriority priority, std::function<void()> fCallback) {
        events_map[type].emplace_back(priority, std::make_unique<Event<>>(std::move(fCallback)));
    };

    void unregisterEvent(EventType type) {
        events_map.erase(type);
    };

    template<EventType type, typename... Args>
    void dispatchEvent(Args&&... args) {
        auto iter = events_map.find(type);
        if (iter != events_map.end()) {
            auto& list = iter->second;
            std::sort(list.begin(), list.end(), [](const auto& a, const auto& b) {
                return a.first > b.first;
            });

            std::tuple<Args...> arguments(std::forward<Args>(args)...);
            for (const auto& event : list) {
                if (event.second) {
                    static_cast<const Event<Args...>*>(event.second.get())->invoke(&arguments);
                };
            };
        };
    };

    std::map<EventType, std::vector<std::pair<EventPriority, std::unique_ptr<BaseEvent>>>> const& getEvents() const {
        return events_map;
    };

    ~EventDispatcher() = default;
private:
    std::map<EventType, std::vector<std::pair<EventPriority, std::unique_ptr<BaseEvent>>>> events_map;
};