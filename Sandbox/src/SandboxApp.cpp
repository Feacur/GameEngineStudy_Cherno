#include "GES.h"
#include "GES/Core/EntryPoint.h"

#include "Example.h"
#include "Sandbox2D.h"

#if !defined(GES_BYPASS_VENDOR_HEADERS)
	#include <imgui.h>
#endif

class Sandbox : public GES::Application
{
public:
	Sandbox()
	{
		ImGui::SetCurrentContext(GetImGuiLayer()->GetImGuiContext());
		// PushLayer(new ExampleLayer());
		PushLayer(new Sandbox2D());
	}
};

GES::Scope<GES::Application> GES::CreateApplication()
{
	return GES::CreateScope<Sandbox>();
}
