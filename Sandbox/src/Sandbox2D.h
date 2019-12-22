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
	GES::Orthographic2dCameraController m_CameraController;
};
