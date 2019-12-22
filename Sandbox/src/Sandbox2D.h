#pragma once
#include "GES.h"

class Sandbox2D : public GES::Layer
{
public:
	Sandbox2D();
	~Sandbox2D() = default;

	void OnAttach() override;
	void OnDetach() override;

	void OnUpdate(GES::Timestep ts) override;
	void OnImGuiRender() override;
	void OnEvent(GES::Event& e) override;

private:
	GES::ShaderLibrary m_ShaderLibrary;
	GES::Ref<GES::VertexArray> m_SquareVA;

	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };

	GES::Orthographic2dCameraController m_CameraController;
};
