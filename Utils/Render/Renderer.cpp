#include "Renderer.h"

bool Renderer::init = false;
ImDrawList* Renderer::drawList = nullptr;

#define RELEASE_AND_NULLIFY(ptr) \
    if (ptr) {                   \
        ptr->Release();          \
        ptr = nullptr;           \
    };

auto Renderer::getSCVtable(void) -> unsigned long long* {

    static unsigned long long* vtable = nullptr;

    if(vtable != nullptr)
        return vtable;
    
    ID3D12CommandAllocator* commandAllocator = nullptr;
    ID3D12GraphicsCommandList* commandList = nullptr;
    ID3D12CommandQueue* commandQueue = nullptr;
    IDXGIAdapter* adapter = nullptr;
    IDXGIFactory* factory = nullptr;
    ID3D12Device* device = nullptr;

    WNDCLASSEX windowClass;
    DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
    
    windowClass.cbSize = sizeof(WNDCLASSEX);
    windowClass.style = CS_HREDRAW | CS_VREDRAW;
    windowClass.lpfnWndProc = DefWindowProc;
    windowClass.cbClsExtra = 0;
    windowClass.cbWndExtra = 0;
    windowClass.hInstance = GetModuleHandle(NULL);
    windowClass.hIcon = NULL;
    windowClass.hCursor = NULL;
    windowClass.hbrBackground = NULL;
    windowClass.lpszMenuName = NULL;
    windowClass.lpszClassName = "SwapChain Window";
    windowClass.hIconSm = NULL;

    ::RegisterClassEx(&windowClass);
    HWND window = ::CreateWindow(windowClass.lpszClassName, "DirectX Window", WS_OVERLAPPEDWINDOW, 0, 0, 100, 100, NULL, NULL, windowClass.hInstance, NULL);

    HMODULE libDXGI;
    HMODULE libD3D12;

    if ((libDXGI = ::GetModuleHandle("dxgi.dll")) == NULL || (libD3D12 = ::GetModuleHandle("d3d12.dll")) == NULL) {
        goto safe_release;
    };

    void* CreateDXGIFactory;
    if ((CreateDXGIFactory = ::GetProcAddress(libDXGI, "CreateDXGIFactory")) == NULL) {
        goto safe_release;
    };

    if (((long(__stdcall*)(const IID&, void**))(CreateDXGIFactory))(__uuidof(IDXGIFactory), (void**)&factory) < 0) {
        goto safe_release;
    };

    if (factory->EnumAdapters(0, &adapter) == DXGI_ERROR_NOT_FOUND) {
        goto safe_release;
    };

    void* D3D12CreateDevice;
    if ((D3D12CreateDevice = ::GetProcAddress(libD3D12, "D3D12CreateDevice")) == NULL) {
        goto safe_release;
    };

    if (((long(__stdcall*)(IUnknown*, D3D_FEATURE_LEVEL, const IID&, void**))(D3D12CreateDevice))(adapter, D3D_FEATURE_LEVEL_11_0, __uuidof(ID3D12Device), (void**)&device) < 0) {
        goto safe_release;
    };

    D3D12_COMMAND_QUEUE_DESC queueDesc;
    queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
    queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
    queueDesc.Priority = 0;
    queueDesc.NodeMask = 0;

    if (device->CreateCommandQueue(&queueDesc, __uuidof(ID3D12CommandQueue), (void**)&commandQueue) < 0) {
        goto safe_release;
    };

    if (device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, __uuidof(ID3D12CommandAllocator), (void**)&commandAllocator) < 0) {
        goto safe_release;
    };

    if (device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, commandAllocator, NULL, __uuidof(ID3D12GraphicsCommandList), (void**)&commandList) < 0) {
        goto safe_release;
    };

    DXGI_RATIONAL refreshRate;
    DXGI_MODE_DESC bufferDesc;

    refreshRate.Numerator = 0;
    refreshRate.Denominator = 1;

    bufferDesc.Width = 100;
    bufferDesc.Height = 100;
    bufferDesc.RefreshRate = refreshRate;
    bufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    bufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
    bufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;

    swapChainDesc.Windowed = 1;
    swapChainDesc.BufferCount = 2;
    swapChainDesc.SampleDesc.Count = 1;
    swapChainDesc.OutputWindow = window;
    swapChainDesc.SampleDesc.Quality = 0;
    swapChainDesc.BufferDesc = bufferDesc;
    swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

    IDXGISwapChain* swapChain;
    if (factory->CreateSwapChain(commandQueue, &swapChainDesc, &swapChain) < 0)
        goto safe_release;

    vtable = (unsigned long long*)::calloc(150, sizeof(unsigned long long));
    ::memcpy(vtable, *(unsigned long long**)device, 44 * sizeof(unsigned long long));
    ::memcpy(vtable + 44, *(unsigned long long**)commandQueue, 19 * sizeof(unsigned long long));
    ::memcpy(vtable + 44 + 19, *(unsigned long long**)commandAllocator, 9 * sizeof(unsigned long long));
    ::memcpy(vtable + 44 + 19 + 9, *(unsigned long long**)commandList, 60 * sizeof(unsigned long long));
    ::memcpy(vtable + 44 + 19 + 9 + 60, *(unsigned long long**)swapChain, 18 * sizeof(unsigned long long));

    return vtable;

safe_release:
    if(device)
        RELEASE_AND_NULLIFY(device);
    
    if(swapChain)
        RELEASE_AND_NULLIFY(swapChain);
    
    if(commandAllocator)
        RELEASE_AND_NULLIFY(commandAllocator);
    
    if(commandQueue)
        RELEASE_AND_NULLIFY(commandQueue);
    
    if(commandList)
        RELEASE_AND_NULLIFY(commandList);
    
    ::DestroyWindow(window);
    ::UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);

    return nullptr;

};

auto Renderer::drawText(ImVec2 textPos, std::string text, float fontSize, ImColor color) -> void {

    if(!Renderer::drawList)
        return;
    
    Renderer::drawList->AddText(ImGui::GetFont(), fontSize, textPos, ImColor(color.Value.x / 255.f, color.Value.y / 255.f, color.Value.z / 255.f, color.Value.w), text.c_str());

};