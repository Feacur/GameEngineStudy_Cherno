#include "GameLayer.h"

#include <imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace GES;

GameLayer::GameLayer()
	: Layer("GameLayer")
	, m_Camera(-16, 16, -9, 9)
{
	Random::Init();
}

void GameLayer::OnAttach()
{
	m_Level.Init();

	ImGuiIO io = ImGui::GetIO();
	m_Font = io.Fonts->AddFontFromFileTTF("assets/fonts/OpenSans-Regular.ttf", 120.0f);
}

void GameLayer::OnDetach()
{
}

void GameLayer::OnUpdate(GES::Timestep ts)
{
	m_Time += ts;
	if ((int)(m_Time * 10.0f) % 8 > 4)
		m_Blink = !m_Blink;

	if (m_Level.IsGameOver())
		m_State = GameState::GameOver;

	const auto& playerPos = m_Level.GetPlayer().GetPosition();
	m_Camera.SetPosition({ playerPos.x, playerPos.y, 0.0f });
	m_Camera.RecalculateViewMatrix();

	switch (m_State)
	{
		case GameState::Play:
		{
			m_Level.OnUpdate(ts);
			break;
		}
	}

	GES::RendererCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
	GES::RendererCommand::Clear();

	// Render
	GES::Renderer2D::BeginScene(m_Camera);
	m_Level.OnRender();
	GES::Renderer2D::EndScene();
}

void GameLayer::OnImGuiRender()
{
	//ImGui::Begin("Settings");
	//m_Level.OnImGuiRender();
	//ImGui::End();

	// UI?

	switch (m_State)
	{
		case GameState::Play:
		{
			uint32 playerScore = m_Level.GetPlayer().GetScore();
			std::string scoreStr = std::string("Score: ") + std::to_string(playerScore);
			ImGui::GetForegroundDrawList()->AddText(m_Font, 48.0f, ImGui::GetWindowPos(), 0xffffffff, scoreStr.c_str());
			break;
		}
		case GameState::MainMenu:
		{
			auto pos = ImGui::GetWindowPos();
			auto width = Application::Get().GetWindow().GetWidth();
			auto height = Application::Get().GetWindow().GetHeight();
			pos.x += width * 0.5f - 300.0f;
			pos.y += 50.0f;
			if (m_Blink)
				ImGui::GetForegroundDrawList()->AddText(m_Font, 120.0f, pos, 0xffffffff, "Click to Play!");
			break;
		}
		case GameState::GameOver:
		{
			auto pos = ImGui::GetWindowPos();
			auto width = Application::Get().GetWindow().GetWidth();
			auto height = Application::Get().GetWindow().GetHeight();
			pos.x += width * 0.5f - 300.0f;
			pos.y += 50.0f;
			if (m_Blink)
				ImGui::GetForegroundDrawList()->AddText(m_Font, 120.0f, pos, 0xffffffff, "Click to Play!");

			pos.x += 200.0f;
			pos.y += 150.0f;
			uint32 playerScore = m_Level.GetPlayer().GetScore();
			std::string scoreStr = std::string("Score: ") + std::to_string(playerScore);
			ImGui::GetForegroundDrawList()->AddText(m_Font, 48.0f, pos, 0xffffffff, scoreStr.c_str());
			break;
		}
	}
}

void GameLayer::OnEvent(GES::Event& e)
{
	EventDispatcher dispatcher(e);
	dispatcher.Dispatch<MouseButtonPressedEvent>(BIND_EVENT_FN(GameLayer::OnMouseButtonPressed));
	dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(GameLayer::OnWindowResized));
}

bool GameLayer::OnMouseButtonPressed(GES::MouseButtonPressedEvent& e)
{
	if (m_State == GameState::GameOver)
		m_Level.Reset();

	m_State = GameState::Play;
	return false;
}

bool GameLayer::OnWindowResized(WindowResizeEvent const & e)
{
	GES_PROFILE_FUNCTION();
	float aspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
	float zoomLevel = 10.0f;
	m_Camera.SetProjection(-aspectRatio * zoomLevel, aspectRatio * zoomLevel, -zoomLevel, zoomLevel);
	return false;
}
