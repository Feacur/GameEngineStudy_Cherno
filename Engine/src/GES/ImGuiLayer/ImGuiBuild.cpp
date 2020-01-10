#include "ges_pch.h"

#define IMGUI_IMPL_OPENGL_LOADER_GLAD
#include <examples/imgui_impl_opengl3.cpp>
#include <examples/imgui_impl_glfw.cpp>

#if defined(SHIPPING)
	#define IMGUI_DISABLE_DEMO_WINDOWS
#endif
// #include <imgui_demo.cpp> // ImGui::ShowDemoWindow
