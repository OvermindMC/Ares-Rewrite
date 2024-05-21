#pragma once

#include <functional>
#include <map>

enum class EventType {
    /* Client Internal Events*/
    Module_Tick = 1, Module_Toggle = 2,
    
    /* Window */
    Present_Tick = 3,
    Present_Resize = 4,
    
    /* Other */

    Level_Tick = 5,

    KeyInput = 6,
    MouseInput = 7,

    ScreenControllerTick = 8
};

template<typename... TArgs>
class Event {
public:
    std::function<void(TArgs...)> callback;
    Event(std::function<void(TArgs...)> fn) : callback(fn) {};
};