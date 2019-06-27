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
		if (GES::Input::IsKeyPressed(GES_KEY_TAB))
			GES_TRACE("Tab key is pressed (poll)!");
	}

	void OnEvent(GES::Event& event) override
	{
		if (event.GetEventType() == GES::EventType::KeyPressed)
		{
			GES::KeyPressedEvent& e = (GES::KeyPressedEvent&)event;
			if (e.GetKeyCode() == GES_KEY_TAB)
				GES_TRACE("Tab key is pressed (event)!");
			GES_TRACE("{0}", (char)e.GetKeyCode());
		}
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
};

GES::Application *GES::CreateApplication()
{
	return new Sandbox();
}
