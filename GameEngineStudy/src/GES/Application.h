#pragma once

#include "Core.h"
#include "GES/LayerStack.h"
#include "Events/Event.h"
#include "Window.h"

#include "ImGuiLayer/ImGuiLayer.h"

#include "Renderer/Buffer.h"
#include "Renderer/Shader.h"

namespace GES {
	#ifdef GES_SHARED
	GES_TEMPLATE template class GES_API std::_Compressed_pair<std::default_delete<Window>, Window *, true>;
	GES_TEMPLATE template class GES_API std::unique_ptr<Window>;
	#endif
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
		std::unique_ptr<Window> m_Window;
		ImGuiLayer * m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;

		uint32 m_VertexArray;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
		std::unique_ptr<Shader> m_Shader;

		static Application * s_Instance;
	};

	Application *CreateApplication();
}
