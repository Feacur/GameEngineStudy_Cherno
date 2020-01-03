#pragma once
#include "GES.h"

#include "Player.h"
#include "Level.h"
#include "ParticleSystem.h"

namespace FloatyRocket
{
	class MainLayer : public GES::Layer
	{
	public:
		MainLayer();
		~MainLayer() = default;

		void OnAttach() override;
		void OnDetach() override;

		void OnUpdate(GES::Timestep ts) override;
		void OnImGuiRender() override;
		void OnEvent(GES::Event& e) override;

	private:
		bool OnWindowResized(GES::WindowResizeEvent const & e);

	private:
		GES::Orthographic2dCamera m_Camera;

		Player m_Player;
		Level m_Level;
		ParticleSystem m_ParticleSystem;

		GES::Ref<GES::Texture2D> m_PlayerTexture;
		GES::Ref<GES::Texture2D> m_LevelTexture;
		GES::Ref<GES::Shader> m_PostVignette;
	};
}
