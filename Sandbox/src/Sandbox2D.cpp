#include "Sandbox2D.h"

#if defined(GES_BYPASS_VENDOR_HEADERS)
	#include <vector>
#endif

#include <imgui.h>

#include "Profiler.h"
#define PROFILE_SCOPE(name) ScopedProfiler TOKENIZE_A_MACRO(profiler, __LINE__)(name,\
	[&](ProfileResult profileResult) { m_ProfileResults.push_back(profileResult); }\
)

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D")
	, m_CameraController(1280.0f / 720.0f)
{
}

void Sandbox2D::OnAttach()
{
	m_CheckerboardTexture = GES::Texture2D::Create("assets/textures/checkerboard.png");
}

void Sandbox2D::OnDetach()
{

}

void Sandbox2D::OnUpdate(GES::Timestep ts)
{
	PROFILE_SCOPE("Sandbox2D::OnUpdate");

	// Update
	{
		PROFILE_SCOPE("CameraController::OnUpdate");
		m_CameraController.OnUpdate(ts);
	}

	// Render
	{
		PROFILE_SCOPE("Renderer -> clear");
		GES::RendererCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		GES::RendererCommand::Clear();
	}

	{
		PROFILE_SCOPE("Renderer -> draw");
		GES::Renderer2D::BeginScene(m_CameraController.GetCamera());
		// GES::Renderer2D::DrawQuad({ 0.0f, 0.0f }, { 1.0f, 1.0f }, { 0.8f, 0.2f, 0.3f, 1.0f });
		GES::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
		GES::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
		GES::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 10.0f, 10.0f }, m_CheckerboardTexture);
		GES::Renderer2D::EndScene();
	}
}

void Sandbox2D::OnImGuiRender()
{
	// ImGui::Begin("Settings");
	// ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	// ImGui::End();

	for (auto & result : m_ProfileResults)
	{
		char label[50];
		strcpy(label, "%.3fms ");
		strcat(label, result.Name);
		ImGui::Text(label, result.Time);
	}
	m_ProfileResults.clear();
}

void Sandbox2D::OnEvent(GES::Event& e)
{
	m_CameraController.OnEvent(e);
}
