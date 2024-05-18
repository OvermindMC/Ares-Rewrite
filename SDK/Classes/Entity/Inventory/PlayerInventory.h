#pragma once

#include "Container/Container.h"

class PlayerInventory {
private:
	char pad_0x0000[0x10]; //0x0000
public:
	int hotbarSlot;        //0x0010
private:
	char pad_0x0018[0xA8]; //0x0018
public:
	Container* container; //0x00C0
};