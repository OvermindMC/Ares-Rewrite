#include "Level_Hook.h"

Level_Hook::Level_Hook(Manager* mgr) : Hook<void, Level*>(mgr, "Level_Hook", mgr->getSig<void**>("Level_VTable")[99],
    [&](Level* level) -> void {

        auto player = MC::getClientInstance()->getPlayer();

        if(player)
            player->setIsOnGround(true);

        return this->_Func(level);
    }
){};