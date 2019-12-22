#include "ges_pch.h"
#include "Application.h"

#include "Log.h"

// #include "KeyCodes.h"
// #include "MouseCodes.h"
#include "Input.h"

#include "GES/Events/Event.h"
#include "GES/Events/ApplicationEvent.h"

#include "Window.h"

#include "GES/Renderer/RendererCommand.h"
#include "GES/Renderer/Renderer.h"
#include "GES/Renderer/Renderer2D.h"

#include "GES/ImGuiLayer/ImGuiLayer.h"

#include <GLFW/glfw3.h>

namespace GES {
	Application * Application::s_Instance = nullptr;

	Application::Application()
	{
		GES_CORE_ASSERT(!s_Instance, "Duplicate Application intance");
		s_Instance = this;

		m_Window = Window::Create();
		m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));

		RendererCommand::Init();
		Renderer::Init();
		Renderer2D::Init();

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
	}

	Application::~Application()
	{
		RendererCommand::Shutdown();
		Renderer::Shutdown();
		Renderer2D::Shutdown();
	}

	void Application::Run()
	{
		m_LastFrameTime = (float)glfwGetTime();
		while (m_Running)
		{
			float time = (float)glfwGetTime();
			Timestep timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;

			if (!m_Minimized)
			{
				for (Layer* layer: m_LayerStack)
					layer->OnUpdate(timestep);
			}

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		}
	}

	void Application::OnEvent(Event & e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(Application::OnWindowResize));

		for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); ++it)
		{
			(*it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
	}

	bool Application::OnWindowClose(WindowCloseEvent & e)
	{
		m_Running = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent & e)
	{
		if (e.GetWidth() == 0 || e.GetHeight() == 0)
		{
			m_Minimized = true;
			return false;
		}

		m_Minimized = false;
		RendererCommand::SetViewport(0, 0, e.GetWidth(), e.GetHeight());

		return false;
	}
}
