#pragma once

#include "../../Mem/Mem.h"

class Actor;
class Player;

class GameMode {
private:
    virtual ~GameMode();
public:
    virtual bool startDestroyBlock(Vec3i* pos, unsigned __int8 face, bool hasDestroyedBlock);
    virtual bool destroyBlock(Vec3i* pos, unsigned __int8 face);
    virtual bool continueDestroyBlock(Vec3i* pos, unsigned __int8 face, Vec3 const& playerPos, bool hasDestroyedBlock);
    virtual void stopDestroyBlock(Vec3i* pos);
    virtual void startBuildBlock(Vec3i* pos, unsigned __int8 face);
    virtual bool buildBlock(Vec3i* pos, unsigned __int8 face, bool);
    virtual void continueBuildBlock(Vec3i* pos, unsigned __int8 face);
    virtual void stopBuildBlock();
    virtual void tick();
    virtual float getPickRange(enum InputMode* currentInputMode, bool isVR);
    virtual bool useItem(class ItemStack*);
    virtual class InteractionResult useItemOn(
        class ItemStack&      item,
        Vec3i*                at,
        unsigned __int8       face,
        Vec3*                 hit,
        class Block const*    targetBlock
    );
    virtual bool interact(Actor* entity, Vec3* location);
    virtual bool attack(Actor* entity);
    virtual void releaseUsingItem();
    virtual void setTrialMode(bool isEnabled);
    virtual bool isInTrialMode();

    Player* player;
};