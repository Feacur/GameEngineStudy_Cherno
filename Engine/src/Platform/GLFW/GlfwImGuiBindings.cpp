#include "ges_pch.h"
#include "GlfwImGuiBindings.h"

#include "GES/Debug/Instrumentor.h"
#include "GES/Debug/Code.h"

#include <imgui.h>

#define IMGUI_IMPL_OPENGL_LOADER_GLAD
#include <examples/imgui_impl_opengl3.cpp>
#include <examples/imgui_impl_glfw.cpp>

#include <GLFW/glfw3.h>

namespace GES
{
	GlfwImGuiBindings::GlfwImGuiBindings()
	{
		GES_PROFILE_FUNCTION();
		s_Instance = this;
	}

	void GlfwImGuiBindings::InitImpl()
	{
		GES_PROFILE_FUNCTION();
		GLFWwindow * window = glfwGetCurrentContext();
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 410");
	}

	void GlfwImGuiBindings::ShutdownImpl()
	{
		GES_PROFILE_FUNCTION();
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
	}
	
	void GlfwImGuiBindings::BeginImpl()
	{
		GES_PROFILE_FUNCTION();
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
	}

	void GlfwImGuiBindings::EndImpl()
	{
		GES_PROFILE_FUNCTION();
		ImGuiIO& io = ImGui::GetIO();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow * window = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(window);
		}
	}
}
