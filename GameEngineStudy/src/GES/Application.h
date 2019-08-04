#pragma once

#include "Core.h"
#include "GES/LayerStack.h"
#include "Window.h"

#include "ImGuiLayer/ImGuiLayer.h"

// #include <vector>
#include <memory> // std::unique_ptr, std::shared_ptr

namespace GES {
	#ifdef GES_SHARED
	GES_TEMPLATE template class GES_API std::_Compressed_pair<std::default_delete<Window>, Window *, true>;
	GES_TEMPLATE template class GES_API std::unique_ptr<Window>;
	#endif
	
	class Event;
	class WindowCloseEvent;

	class GES_API Application
	{
	public:
		Application();
		virtual ~Application() = default;
	public:
		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }
		inline ImGuiContext* GetImGuiContext() { return m_ImGuiLayer->GetImGuiContext(); }
	public:
		void Run();
		void OnEvent(Event & e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

	private:
		bool OnWindowClose(WindowCloseEvent & e);

	private:
		std::unique_ptr<Window> m_Window;
		ImGuiLayer * m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;

	private:
		static Application * s_Instance;
	};

	Application *CreateApplication();
}
