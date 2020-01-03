#include "Sandbox2D.h"

#if defined(GES_BYPASS_VENDOR_HEADERS)
	#include <vector>
#endif

#include <imgui.h>

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D")
	, m_CameraController(1280.0f / 720.0f)
{
	GES_PROFILE_FUNCTION();
}

void Sandbox2D::OnAttach()
{
	GES_PROFILE_FUNCTION();
	m_CheckerboardTexture = GES::Texture2D::CreatePath("assets/textures/checkerboard.png");
}

void Sandbox2D::OnDetach()
{
	GES_PROFILE_FUNCTION();
	m_CheckerboardTexture = nullptr;
}

void Sandbox2D::OnUpdate(GES::Timestep ts)
{
	GES_PROFILE_FUNCTION();

	// Update
	{
		GES_PROFILE_SCOPE("CameraController::OnUpdate");
		m_CameraController.OnUpdate(ts);
	}

	// Render
	{
		GES_PROFILE_SCOPE("Renderer -> clear");
		GES::RendererCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		GES::RendererCommand::Clear();
	}

	{
		GES_PROFILE_SCOPE("Renderer -> draw");
		GES::Renderer2D::BeginScene(m_CameraController.GetCamera());
		GES::Renderer2D::DrawQuad({ -1.0f, 0.0f, 0.1f }, { 0.8f, 0.8f }, 0.0f, { 0.8f, 0.2f, 0.3f, 1.0f });
		GES::Renderer2D::DrawQuad({ 0.5f, -0.5f, 0.1f }, { 0.5f, 0.75f }, 0.0f, { 0.2f, 0.3f, 0.8f, 1.0f });
		GES::Renderer2D::DrawQuad({ 0.0f, 0.0f, 0.9f }, { 10.0f, 10.0f }, 0.0f, m_CheckerboardTexture);
		GES::Renderer2D::EndScene();
	}
}

void Sandbox2D::OnImGuiRender()
{
	GES_PROFILE_FUNCTION();

	static bool profilerIsRunning = false;
	profilerIsRunning = GES_PROFILE_GET_ENABLED();

	ImGui::Begin("Profiler");
	ImGui::Checkbox("Enable", &profilerIsRunning);
	ImGui::End();

	GES_PROFILE_SET_ENABLED(profilerIsRunning);
	
	// ImGui::Begin("Settings");
	// ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	// ImGui::End();

	// for (auto & result : m_ProfileResults)
	// {
	// 	char label[50];
	// 	strcpy(label, "%.3fms ");
	// 	strcat(label, result.Name);
	// 	ImGui::Text(label, result.Time);
	// }
	// m_ProfileResults.clear();
}

void Sandbox2D::OnEvent(GES::Event& e)
{
	GES_PROFILE_FUNCTION();
	m_CameraController.OnEvent(e);
}
