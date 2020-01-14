#pragma once
#include "Code.h"

#include "LayerStack.h"

namespace GES {
	#if defined(GES_SHARED)
	GES_EXTERN template class GES_DLL std::_Compressed_pair<std::default_delete<Window>, Window *, true>;
	GES_EXTERN template class GES_DLL std::unique_ptr<Window>;
	#endif
	
	class Window;
	class Event;
	class WindowCloseEvent;
	class WindowResizeEvent;
	class ImGuiLayer;

	class GES_DLL Application
	{
	public:
		Application();
		virtual ~Application();

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
		Scope<Window> m_Window;
		ImGuiLayer * m_ImGuiLayer;
		bool m_Running = true;
		bool m_Minimized = false;
		LayerStack m_LayerStack;
		r32 m_LastFrameTime;

	private:
		static Application * s_Instance;
	};
}
