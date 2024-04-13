#pragma once

#include <functional>
#include <map>

enum class EventType {
    /* Client Internal Events*/
    Module_Tick = 1, Module_Toggle = 2,
    
    /* Other */
    Present_Tick = 3,
    Level_Tick = 4,

    KeyInput = 5
};

template<typename... TArgs>
class Event {
public:
    std::function<void(TArgs...)> callback;
    Event(std::function<void(TArgs...)> fn) : callback(fn) {};
};