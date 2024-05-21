#include "ResizeBuffers.h"

SwapChain_ResizeBuffers::SwapChain_ResizeBuffers(Manager* mgr) : Hook<HRESULT, IDXGISwapChain*, int, int, int, DXGI_FORMAT, int>(mgr, "SwapChain_ResizeBuffers", (void*)Renderer::getSCVtable()[145],
    [&](IDXGISwapChain* swapChain, int bufferCount, int width, int height, DXGI_FORMAT format, int flags) -> HRESULT {

        this->mgr->dispatchEvent<EventType::Present_Resize>();
        return this->_Func(swapChain, bufferCount, width, height, format, flags);

    }
) {};