#pragma once

#include "../../Hook.h"

class SwapChain_PresentHook : public Hook<HRESULT, IDXGISwapChain3*, UINT, UINT> {
public:
    SwapChain_PresentHook(Manager*);
};