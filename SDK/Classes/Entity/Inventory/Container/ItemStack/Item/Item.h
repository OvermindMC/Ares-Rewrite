#pragma once

#include "../../../../../../../Mem/Mem.h"

class Item {
public:
    auto isBlock(void) -> bool {
        return this ? *(uintptr_t**)((uintptr_t)(this) + 0x1C8) != nullptr : false;
    };
public:
    BUILD_ACCESS(int, id, 0xA2);
    BUILD_ACCESS(std::string, name, 0xD0);
    BUILD_ACCESS(std::string, name_id, 0x120);
public:
    auto isSword(void) -> bool {
        switch(this->id) {
            case 311:
                return true; /* Wooden Sword */
            break;
            case 315:
                return true; /* Stone Sword */
            break;
            case 310:
                return true; /* Iron Sword */
            break;
            case 326:
                return true; /* Golden Sword */
            break;
            case 319:
                return true; /* Diamond Sword */
            break;
            case 618:
                return true; /* Netherite Sword */
            break;
            
            default:
                return false;
        };
    };

    auto isAxe(void) -> bool {
        switch(this->id) {
            case 314:
                return true; /* Wooden Axe */
            break;
            case 318:
                return true; /* Stone Axe */
            break;
            case 301:
                return true; /* Iron Axe */
            break;
            case 329:
                return true; /* Golden Axe */
            break;
            case 322:
                return true; /* Diamond Axe */
            break;
            case 621:
                return true; /* Netherite Axe */
            break;
            
            default:
                return false;
        };
    };

    auto isPickaxe(void) -> bool {
        switch(this->id) {
            case 313:
                return true; /* Wooden Pickaxe */
            break;
            case 317:
                return true; /* Stone Pickaxe */
            break;
            case 300:
                return true; /* Iron Pickaxe */
            break;
            case 328:
                return true; /* Golden Pickaxe */
            break;
            case 321:
                return true; /* Diamond Pickaxe */
            break;
            case 620:
                return true; /* Netherite Pickaxe */
            break;
            
            default:
                return false;
        };
    };

    auto isShovel(void) -> bool {
        switch(this->id) {
            case 312:
                return true; /* Wooden Shovel */
            break;
            case 316:
                return true; /* Stone Shovel */
            break;
            case 299:
                return true; /* Iron Shovel */
            break;
            case 327:
                return true; /* Golden Shovel */
            break;
            case 320:
                return true; /* Diamond Shovel */
            break;
            case 619:
                return true; /* Netherite Shovel */
            break;
            
            default:
                return false;
        };
    };
};