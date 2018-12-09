#include "ges_pch.h"
#include "Application.h"

#include "GES/Events/ApplicationEvent.h"
#include "GES/Log.h"

namespace GES {
	Application::Application()
	{
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		WindowResizeEvent e(1280, 720);
		if (e.IsInCategory(EventCategory::Application))
		{
			GES_TRACE(e);
		}
		if (e.IsInCategory(EventCategory::Input))
		{
			GES_TRACE(e);
		}
		while (true) { /**/ }
	}
}
