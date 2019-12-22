#pragma once
#include "GES.h"

class ExampleLayer : public GES::Layer
{
public:
	ExampleLayer();
	~ExampleLayer() = default;

	void OnUpdate(GES::Timestep ts) override;
	void OnImGuiRender() override;
	void OnEvent(GES::Event & e) override;

private:
	GES::ShaderLibrary m_ShaderLibrary;
	GES::Ref<GES::VertexArray> m_VertexArrayTriangle;
	GES::Ref<GES::VertexArray> m_VertexArraySquare;
	GES::Ref<GES::Texture2D> m_TextureCheckerboard;
	GES::Ref<GES::Texture2D> m_TextureChernoLogo;

	GES::Orthographic2dCameraController m_CameraController;
};
