#include <GES.h>

class ExampleLayer : public GES::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
	}

	void OnUpdate() override
	{
		GES_INFO("ExampleLayer::Update");
	}

	void OnEvent(GES::Event& event) override
	{
		GES_TRACE("{0}", event);
	}

};

class Sandbox : public GES::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		PushLayer(new GES::ImGuiLayer());
	}

	~Sandbox()
	{
	}
};

GES::Application *GES::CreateApplication()
{
	return new Sandbox();
}
