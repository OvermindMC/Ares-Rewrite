#pragma once

#include <functional>
#include <map>

enum class EventType {
    Module_Tick = 1, Module_Toggle = 2
};

template<typename... TArgs>
class Event {
public:
    std::function<void(TArgs...)> callback;
    Event(std::function<void(TArgs...)> fn) : callback(fn) {};
};