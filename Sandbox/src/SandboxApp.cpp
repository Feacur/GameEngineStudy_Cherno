#include "GES.h"
#include "GES/Core/EntryPoint.h"

// #include "Example.h"
// #include "Sandbox2D.h"
#include "FloatyRocket/MainLayer.h"

#include <imgui.h>

class Sandbox : public GES::Application
{
public:
	Sandbox()
	{
		GES_PROFILE_FUNCTION();
		ImGui::SetCurrentContext(GetImGuiLayer()->GetImGuiContext());
		// PushLayer(new ExampleLayer());
		// PushLayer(new Sandbox2D());
		PushLayer(new FloatyRocket::MainLayer());
	}
};

GES::Application * GES::CreateApplication()
{
	GES_PROFILE_FUNCTION();
	return new Sandbox();
}
