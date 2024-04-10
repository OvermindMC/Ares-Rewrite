#pragma once

#include "ImFx/ImFx.h"
#include "ImGui/DroidSans.hpp"
#include "ImGui/imgui_impl_dx11.h"
#include "ImGui/imgui_impl_win32.h"

#include <string>

class Renderer {
private:
    static bool initialized;
    static ImDrawList* drawList;
private:
    static IDXGISwapChain3* sc;
private:
    static ID3D11DeviceContext* context;
    static ID3D11Texture2D* backBuffer;
    static IDXGISurface* surfaceBuffer;
    static ID3D11RenderTargetView* tv;
public:
    static auto getSCVtable(void) -> unsigned long long*;
    static auto getWindow(void) -> HWND;
public:
    static auto init(IDXGISwapChain3*, ID3D11Device*) -> bool;
    static auto cleanup(bool) -> void;
public:
    static auto newFrame(void) -> void;
    static auto endFrame(void) -> void;
public:
    static auto setDrawList(ImDrawList*) -> void;
public:
    static auto drawText(ImVec2, std::string, float, ImColor) -> void;
};