#include "ges_pch.h"
#include "ImGuiBindings.h"

#if defined(GES_SHIPPING)
	#define IMGUI_DISABLE_DEMO_WINDOWS
#endif
// #include <imgui_demo.cpp> // ImGui::ShowDemoWindow

namespace GES
{
	ImGuiBindings * ImGuiBindings::s_Instance = nullptr;
}
