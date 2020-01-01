#pragma once
#include "GES.h"

#include "Level.h"

struct ImFont;

class GameLayer : public GES::Layer
{
public:
	GameLayer();
	~GameLayer() = default;

	void OnAttach() override;
	void OnDetach() override;

	void OnUpdate(GES::Timestep ts) override;
	void OnImGuiRender() override;
	void OnEvent(GES::Event& e) override;
	bool OnMouseButtonPressed(GES::MouseButtonPressedEvent& e);
	bool OnWindowResized(GES::WindowResizeEvent const & e);

private:
	GES::Orthographic2dCamera m_Camera;
	
	Level m_Level;
	ImFont* m_Font;
	float m_Time = 0.0f;
	bool m_Blink = false;

	enum class GameState
	{
		Play = 0, MainMenu = 1, GameOver = 2
	};

	GameState m_State = GameState::MainMenu;
	uint32 m_Random;
};