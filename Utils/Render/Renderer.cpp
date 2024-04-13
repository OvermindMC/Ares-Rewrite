#include "Renderer.h"
#include "../Debugger/Debugger.h"

bool Renderer::initialized = false;
ImDrawList* Renderer::drawList = nullptr;
IDXGISwapChain3* Renderer::sc = nullptr;

ID3D11DeviceContext* Renderer::context = nullptr;
ID3D11Texture2D* Renderer::backBuffer = nullptr;
IDXGISurface* Renderer::surfaceBuffer = nullptr;
ID3D11RenderTargetView* Renderer::tv = nullptr;

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

auto Renderer::getWindow(void) -> HWND {

    static auto window = (HWND)FindWindowA(nullptr, "Minecraft");
    return window;

};

auto Renderer::init(IDXGISwapChain3* swapChain, ID3D11Device* device) -> bool {

    Renderer::sc = swapChain;

    if(!ImGui::GetCurrentContext()) {
        ImGui::CreateContext();
        ImGui::GetIO().Fonts->AddFontFromMemoryCompressedTTF(DroidSans_compressed_data, DroidSans_compressed_size, 18.f);
    };

    device->GetImmediateContext(&Renderer::context);
    if(!Renderer::context) {
        Debugger::log("Failed to get context");
        return false;
    };
    
    if(FAILED(swapChain->GetBuffer(0, IID_PPV_ARGS(&Renderer::backBuffer)))) {
        Debugger::log("Failed to get back buffer texture");
        return false;
    };
    
    if(FAILED(swapChain->GetBuffer(0, IID_PPV_ARGS(&Renderer::surfaceBuffer)))) {
        Debugger::log("Failed to get surface buffer");
        return false;
    };
    
    if(FAILED(device->CreateRenderTargetView(Renderer::backBuffer, nullptr, &Renderer::tv))) {
        Debugger::log("Failed to create render target view!");
        return false;
    };
    
    if(!Renderer::initialized) {
        Renderer::initialized = true;
        ImGui_ImplWin32_Init(Renderer::getWindow());
        ImGui_ImplDX11_Init(device, Renderer::context);
    };

    return true;

};

auto Renderer::cleanup(bool clearAll) -> void {

    Renderer::initialized = !clearAll;

    if(clearAll && ImGui::GetCurrentContext()) {
        ImGui::DestroyContext();
    };

    if(Renderer::context) {
        Renderer::context->Flush();
        RELEASE_AND_NULLIFY(Renderer::context);
    };

    if(Renderer::backBuffer) {
        RELEASE_AND_NULLIFY(Renderer::backBuffer);
    };

    if(Renderer::surfaceBuffer) {
        RELEASE_AND_NULLIFY(Renderer::surfaceBuffer);
    };

    if(Renderer::tv) {
        RELEASE_AND_NULLIFY(Renderer::tv);
    };

};

auto Renderer::newFrame(void) -> void {

    if(!Renderer::initialized)
        return;
    
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

};

auto Renderer::endFrame(void) -> void {

    ImGui::EndFrame();
    ImGui::Render();
    
    Renderer::context->OMSetRenderTargets(1, &Renderer::tv, nullptr);
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

};

auto Renderer::setDrawList(ImDrawList* list) -> void {

    Renderer::drawList = list;

};

auto Renderer::getTextSize(std::string text, float fontSize) -> ImVec2 {

    auto result = ImVec2(0.f, 0.f);
    
    if(!Renderer::drawList)
        return result;
    
    result = ImGui::GetFont()->CalcTextSizeA(fontSize, 1000.f, -1.f, text.c_str());
    return result;

};

auto Renderer::getTextW(std::string text, float fontSize) -> float {

    return Renderer::getTextSize(text, fontSize).x;

};

auto Renderer::getTextH(std::string text, float fontSize) -> float {

    return Renderer::getTextSize(text, fontSize).y;

};

auto Renderer::drawText(ImVec2 textPos, std::string text, float fontSize, ImColor color) -> void {

    if(!Renderer::drawList)
        return;
    
    Renderer::drawList->AddText(ImGui::GetFont(), fontSize, textPos, ImColor(color.Value.x / 255.f, color.Value.y / 255.f, color.Value.z / 255.f, color.Value.w), text.c_str());

};

auto Renderer::addRect(ImVec4 rectPos, ImColor color, float rounding, float thickness) -> void {

    if(!Renderer::drawList)
        return;
    
    ImDrawFlags flags = 0;
    
    Renderer::drawList->AddRect(
        ImVec2(rectPos.x, rectPos.y), ImVec2(rectPos.z, rectPos.w),
        ImColor(color.Value.x / 255.f, color.Value.y / 255.f, color.Value.z / 255.f, color.Value.w), rounding, flags, thickness
    );
    
};

auto Renderer::fillRect(ImVec4 rectPos, ImColor color, float rounding) -> void {

    if(!Renderer::drawList)
        return;
    
    Renderer::drawList->AddRectFilled(
        ImVec2(rectPos.x, rectPos.y), ImVec2(rectPos.z, rectPos.w),
        ImColor(color.Value.x / 255.f, color.Value.y / 255.f, color.Value.z / 255.f, color.Value.w), rounding
    );

};


LiteRender::Container::~Container(void) {

    delete this->el;

};

auto LiteRender::Container::updateBounds(void) -> void {

    auto size = this->getSize();
    auto space = this->getSpace();
    this->boundsRect = ImVec4(
        this->tPos.x - space, this->tPos.y - space,
        this->tPos.x + (size.x + space), this->tPos.y + (size.y + space)
    );

};

auto LiteRender::Container::getRenderPos(void) -> ImVec2 {

    auto space = this->getSpace();

    return ImVec2(
        this->boundsRect.x + space, this->boundsRect.y + space
    );

};

auto LiteRender::Container::render(void) -> void {

    this->updateBounds();

    auto& style = this->style();
    auto& display = this->display();

    Renderer::fillRect(this->getBounds(), style.getBgColor(), 1.f);
    Renderer::addRect(this->getBounds(), style.getOutlineColor(), 0.f, 1.f);
    Renderer::drawText(this->getRenderPos(), display.getText(), display.getFontSize(), display.getColor());

};


LiteRender::Frame::Frame(std::vector<Container*> elements_list, float fontSize) : elements(elements_list), font_size(fontSize) {

    for(auto el : this->elements) {
        el->display().setFontSize(fontSize);
    };

};

LiteRender::Frame::~Frame(void) {

    for(auto el : this->elements) {
        delete el;
    };

    this->elements.clear();

};

auto LiteRender::Frame::updateBounds(void) -> void {

    auto currPos = ImVec2(this->tPos.x, this->tPos.y);
    auto space = this->getSpace();
    for(auto iter = this->elements.begin(); iter != this->elements.end(); ++iter) {
        auto el = *iter;
        
        el->display().setFontSize(this->font_size);
        el->setPos(currPos);
        el->updateBounds();

        currPos = ImVec2(el->getBounds().z + (el != this->elements.back() ? el->getSpace() : 0.f), (el != this->elements.back() ? this->tPos.y : el->getBounds().w));

    };

    this->boundsRect = ImVec4(this->tPos.x - space, this->tPos.y - space, currPos.x, currPos.y);

};

auto LiteRender::Frame::render(void) -> void {

    this->updateBounds();
    
    for(auto el : this->elements) {
        el->render();
    };

};