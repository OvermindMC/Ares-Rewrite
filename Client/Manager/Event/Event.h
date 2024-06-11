#pragma once

#include <functional>
#include <map>

enum class EventType {
    /* Client Internal Events*/
    Module_Tick = 1, Module_Toggle = 2, Modules_Initialized = 3,
    
    /* Window */
    Present_Tick = 4,
    Present_Resize = 5,
    
    /* Other */

    Level_Tick = 6,

    KeyInput = 7,
    MouseInput = 8,

    ScreenControllerTick = 9,

    Packet_SendToServer = 10
};

template<typename... TArgs>
class Event {
public:
    std::function<void(TArgs...)> callback;
    Event(std::function<void(TArgs...)> fn) : callback(fn) {};
};