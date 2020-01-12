#pragma once
#include "GES.h"

// #if !defined(GES_BYPASS_VENDOR_HEADERS)
// 	#include <vector>
// #endif

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
	GES::Ref<GES::Texture2D> m_CheckerboardTexture;

	// struct ProfileResult
	// {
	// 	cstring Name;
	// 	r32 Time;
	// };
	// std::vector<ProfileResult> m_ProfileResults;
};
