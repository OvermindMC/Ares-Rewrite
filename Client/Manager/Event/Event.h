#pragma once

#include <functional>
#include <map>

enum class EventType {
    /* Client Internal Events*/
    Module_Tick = 1, Module_Toggle = 2,
    
    /* Other */
    Level_Tick = 3
};

template<typename... TArgs>
class Event {
public:
    std::function<void(TArgs...)> callback;
    Event(std::function<void(TArgs...)> fn) : callback(fn) {};
};