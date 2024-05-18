#pragma once

#include "Timer/Timer.h"

class Minecraft {
private:
	char pad_0x0000[0xD8];
public:
	Timer* simTimer;  //0x00D8
	Timer* realTimer; //0x00E0
};