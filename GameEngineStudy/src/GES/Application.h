#pragma once

#include "Core.h"
#include "GES/LayerStack.h"
#include "Events/Event.h"
#include "Window.h"

namespace GES {
	GES_TEMPLATE template class GES_API std::_Compressed_pair<std::default_delete<Window>, Window *, true>;
	GES_TEMPLATE template class GES_API std::unique_ptr<Window>;
	class WindowCloseEvent;

	class GES_API Application
	{
	public:
		Application();
		virtual ~Application();
	public:
		void Run();
		void OnEvent(Event & e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);
	private:
		bool OnWindowClose(WindowCloseEvent & e);
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_layerStack;
	};

	Application *CreateApplication();
}
