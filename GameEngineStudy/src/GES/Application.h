#pragma once
#include "Core.h"

#include "GES/LayerStack.h"

namespace GES {
	#if defined(GES_SHARED)
	GES_TEMPLATE template class GES_API std::_Compressed_pair<std::default_delete<Window>, Window *, true>;
	GES_TEMPLATE template class GES_API std::unique_ptr<Window>;
	#endif
	
	class Window;
	class Event;
	class WindowCloseEvent;
	class WindowResizeEvent;
	class ImGuiLayer;

	class GES_API Application
	{
	public:
		Application();
		virtual ~Application() = default;

	public:
		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }
		void Run();

	protected:
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);
		inline ImGuiLayer* GetImGuiLayer() { return m_ImGuiLayer; }

	private:
		void OnEvent(Event & e);

		bool OnWindowClose(WindowCloseEvent & e);
		bool OnWindowResize(WindowResizeEvent & e);

	private:
		Ref<Window> m_Window;
		ImGuiLayer * m_ImGuiLayer;
		bool m_Running = true;
		bool m_Minimized;
		LayerStack m_LayerStack;
		float m_LastFrameTime;

	private:
		static Application * s_Instance;
	};

	Ref<Application> CreateApplication();
}
