#pragma once

#include "../../Hook.h"

class SwapChain_ResizeBuffers : public Hook<HRESULT, IDXGISwapChain*, int, int, int, DXGI_FORMAT, int> {
public:
    SwapChain_ResizeBuffers(Manager*);
};