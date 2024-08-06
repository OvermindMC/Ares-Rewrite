#pragma once

#include "../../Hook.h"

class LookInp_Hook : public Hook<void, EntityContext&, void*, Vec2&> {
public:
    LookInp_Hook(Manager* mgr);
};