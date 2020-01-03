#include "MainLayer.h"

#include <imgui.h>

namespace FloatyRocket
{
	MainLayer::MainLayer()
		: Layer("MainLayer")
		, m_Camera(-16.0f, 16.0f, -9.0f, 9.0f)
		, m_ParticleSystem(1024)
	{
		GES_PROFILE_FUNCTION();
		m_Player.Reset();
		m_Level.Reset();
	}

	void MainLayer::OnAttach()
	{
		GES_PROFILE_FUNCTION();
		m_PlayerTexture = GES::Texture2D::Create("assets/textures/ship.png");
		m_LevelTexture = GES::Texture2D::Create("assets/textures/triangle.png");
		m_PostVignette = GES::Shader::CreatePath("assets/shaders/post_vignette.glsl");
	}

	void MainLayer::OnDetach()
	{
		GES_PROFILE_FUNCTION();
		m_PlayerTexture = nullptr;
		m_LevelTexture = nullptr;
		m_PostVignette = nullptr;
	}

	void MainLayer::OnUpdate(GES::Timestep ts)
	{
		GES_PROFILE_FUNCTION();

		if (m_Level.IsCollision())
		{
			if (GES::Input::IsKeyPressed(GES_KEY_ESCAPE))
			{
				m_Player.Reset();
				m_Level.Reset();
			}
		}

		if (!m_Level.IsCollision())
		{
			m_Player.OnUpdate(ts, m_ParticleSystem);
			m_Level.OnUpdate(ts, m_Player.GetPosition(), m_Player.GetRotation());

			glm::vec3 cameraPosition(m_Player.GetPosition(), 0.0f);
			m_Camera.SetPosition(cameraPosition);
			m_Camera.RecalculateViewMatrix();
		}

		m_ParticleSystem.OnUpdate(ts);

		// Render
		{
			GES_PROFILE_SCOPE("Renderer -> clear");
			GES::RendererCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
			GES::RendererCommand::Clear();
		}

		{
			GES_PROFILE_SCOPE("Renderer -> draw");
			GES::Renderer2D::BeginScene(m_Camera);
			m_Level.OnRender(m_LevelTexture, m_Player.GetPosition());
			m_ParticleSystem.OnRender();
			m_Player.OnRender(m_PlayerTexture);
			GES::Renderer2D::DrawPost(m_PostVignette, {0.0f, 0.0f, 0.0f, 0.5f});
			GES::Renderer2D::EndScene();
		}
	}

	void MainLayer::OnImGuiRender()
	{
		GES_PROFILE_FUNCTION();
	}

	void MainLayer::OnEvent(GES::Event& e)
	{
		GES_PROFILE_FUNCTION();
	}


	bool MainLayer::OnWindowResized(GES::WindowResizeEvent const & e)
	{
		GES_PROFILE_FUNCTION();
		float aspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
		float zoomLevel = 10.0f;
		m_Camera.SetProjection(-aspectRatio * zoomLevel, aspectRatio * zoomLevel, -zoomLevel, zoomLevel);
		return false;
	}
}
