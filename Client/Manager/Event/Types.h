#pragma once

#include "../../../Mem/Mem.h"
#include "../../../Utils/Utils.h"

enum class EventType {
    BaseTick = 0, OnTick = 1, OnEnable = 2, OnDisable = 3,

    OnLevel = 4, OnGameMode = 5,

    OnKey = 6, OnMouse = 7,
    
    OnFirstPersonLook = 8
};