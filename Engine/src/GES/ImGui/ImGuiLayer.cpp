#include "ges_pch.h"
#include "ImGuiLayer.h"

#include "ImGuiBindings.h"

#include "GES/Debug/Instrumentor.h"
#include "GES/Debug/Code.h"

#include <imgui.h>

namespace GES {
	ImGuiLayer::ImGuiLayer()
		: Layer("ImGuiLayer")
	{
		GES_PROFILE_FUNCTION();
	}

	void ImGuiLayer::OnAttach()
	{
		GES_PROFILE_FUNCTION();
		// Setup Dear ImGui context
		IMGUI_CHECKVERSION();
		m_ImGuiContext = ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
		//io.ConfigViewportsNoAutoMerge = true;
		//io.ConfigViewportsNoTaskBarIcon = true;

		// Setup Dear ImGui style
		ImGui::StyleColorsDark();
		//ImGui::StyleColorsClassic();

		// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}

		// Setup Platform/Renderer bindings
		ImGuiBindings::Init();
	}

	void ImGuiLayer::OnDetach()
	{
		GES_PROFILE_FUNCTION();
		ImGuiBindings::Shutdown();
		ImGui::DestroyContext();
	}

	// void ImGuiLayer::OnImGuiRender()
	// {
	// 	static bool show;
	// 	ImGui::ShowDemoWindow(&show);
	// }
	
	void ImGuiLayer::Begin()
	{
		GES_PROFILE_FUNCTION();
		ImGuiBindings::Begin();
		ImGui::NewFrame();
	}

	void ImGuiLayer::End(r32 width, r32 height)
	{
		GES_PROFILE_FUNCTION();
		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2(width, height);

		// Rendering
		ImGui::Render();
		ImGuiBindings::End();
	}
}
