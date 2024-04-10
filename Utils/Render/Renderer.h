#pragma once

#include "ImFx/ImFx.h"
#include "ImGui/DroidSans.hpp"
#include "ImGui/imgui_impl_dx11.h"
#include "ImGui/imgui_impl_win32.h"

class Renderer {
private:
    static bool init;
public:
    static auto getSCVtable(void) -> unsigned long long*;
};