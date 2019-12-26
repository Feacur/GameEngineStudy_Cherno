#include "GES.h"
#include "GES/Core/EntryPoint.h"

#include "Example.h"
#include "Sandbox2D.h"
#include "ChernoOneHourGame/GameLayer.h"

#if !defined(GES_BYPASS_VENDOR_HEADERS)
	#include <imgui.h>
#endif

class Sandbox : public GES::Application
{
public:
	Sandbox()
	{
		GES_PROFILE_FUNCTION();
		ImGui::SetCurrentContext(GetImGuiLayer()->GetImGuiContext());
		// PushLayer(new ExampleLayer());
		// PushLayer(new Sandbox2D());
		PushLayer(new GameLayer());
	}
};

GES::Application * GES::CreateApplication()
{
	GES_PROFILE_FUNCTION();
	return new Sandbox();
}
