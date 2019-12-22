#include "Sandbox2D.h"

#if !defined(GES_BYPASS_VENDOR_HEADERS)
	#include <imgui.h>
#endif

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
	// Update
	m_CameraController.OnUpdate(ts);

	// Render
	GES::RendererCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
	GES::RendererCommand::Clear();

	GES::Renderer2D::BeginScene(m_CameraController.GetCamera());
	// GES::Renderer2D::DrawQuad({ 0.0f, 0.0f }, { 1.0f, 1.0f }, { 0.8f, 0.2f, 0.3f, 1.0f });
	GES::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
	GES::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
	GES::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 10.0f, 10.0f }, m_CheckerboardTexture);
	GES::Renderer2D::EndScene();
}

void Sandbox2D::OnImGuiRender()
{
	// ImGui::Begin("Settings");
	// ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	// ImGui::End();
}

void Sandbox2D::OnEvent(GES::Event& e)
{
	m_CameraController.OnEvent(e);
}
