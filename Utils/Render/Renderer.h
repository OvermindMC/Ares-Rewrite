#pragma once

#include "ImFx/ImFx.h"
#include "ImGui/DroidSans.hpp"
#include "ImGui/imgui_impl_dx11.h"
#include "ImGui/imgui_impl_win32.h"

#include <string>

class Renderer {
private:
    static bool init;
    static ImDrawList* drawList;
public:
    static auto getSCVtable(void) -> unsigned long long*;
public:
    static auto drawText(ImVec2, std::string, float, ImColor) -> void;
};