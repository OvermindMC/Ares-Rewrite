#include "Present.h"
#include "../../../Notification/Manager.h"

SwapChain_PresentHook::SwapChain_PresentHook(Manager* mgr) : Hook<HRESULT, IDXGISwapChain3*, UINT, UINT>(mgr, "SwapChain_Present", (void*)Renderer::getSCVtable()[140],
    [&](IDXGISwapChain3* swapChain, unsigned int sync_interval, unsigned int flags) -> HRESULT {

        Microsoft::WRL::ComPtr<ID3D11Device> d3d11Device;
        Microsoft::WRL::ComPtr<ID3D12Device> d3d12Device;

        if (!d3d11Device && !d3d12Device) {
            if (FAILED(swapChain->GetDevice(IID_PPV_ARGS(d3d11Device.GetAddressOf()))) && FAILED(swapChain->GetDevice(IID_PPV_ARGS(d3d12Device.GetAddressOf())))) {
                return this->_Func(swapChain, sync_interval, flags);
            };
        };

        if(d3d12Device.Get()) {
            swapChain->ResizeBuffers(0, 0, 0, DXGI_FORMAT_UNKNOWN, 0);
            static_cast<ID3D12Device5*>(d3d12Device.Get())->RemoveDevice();
            return this->_Func(swapChain, sync_interval, flags);
        } else {
            if(!Renderer::init(swapChain, d3d11Device.Get())) {
                Renderer::cleanup(true);
                return this->_Func(swapChain, sync_interval, flags);
            } else {
                Renderer::newFrame();
                Renderer::setDrawList(ImGui::GetBackgroundDrawList());

                this->mgr->dispatchEvent<EventType::Present_Tick>();

                auto nfMgr = this->mgr->client->getNotifMgr();
                if(nfMgr)
                    nfMgr->render();

                Renderer::endFrame();
                Renderer::cleanup(false);
            };
            d3d11Device.Reset();
        };
        
        return this->_Func(swapChain, sync_interval, flags);

    }
) {};