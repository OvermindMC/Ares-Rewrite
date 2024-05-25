#pragma once

#include "../../Hook.h"

class RenderContext_Hook : public Hook<void, void*, void*> {
public:
    RenderContext_Hook(Manager*);
};