#include "ges_pch.h"
#include "Application.h"

// #include "KeyCodes.h"
// #include "MouseCodes.h"
#include "Input.h"

#include "GES/Debug/Log.h"
#include "GES/Debug/Instrumentor.h"
#include "GES/Debug/Code.h"

#include "GES/Events/Event.h"
#include "GES/Events/ApplicationEvent.h"

#include "Window.h"

#include "GES/Renderer/RendererCommand.h"
#include "GES/Renderer/Renderer.h"
#include "GES/Renderer/Renderer2D.h"

#include "GES/ImGui/ImGuiLayer.h"

#include <GLFW/glfw3.h>

namespace GES {
	Application * Application::s_Instance = nullptr;

	Application::Application()
	{
		GES_PROFILE_FUNCTION();
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
		GES_PROFILE_FUNCTION();
		RendererCommand::Shutdown();
		Renderer::Shutdown();
		Renderer2D::Shutdown();
	}

	void Application::Run()
	{
		GES_PROFILE_FUNCTION();
		m_LastFrameTime = (r32)glfwGetTime();
		while (m_Running)
		{
			r32 time = (r32)glfwGetTime();
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
			m_ImGuiLayer->End((r32)m_Window->GetWidth(), (r32)m_Window->GetHeight());

			m_Window->OnUpdate();
		}
	}

	void Application::OnEvent(Event & e)
	{
		GES_PROFILE_FUNCTION();
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
		GES_PROFILE_FUNCTION();
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* layer)
	{
		GES_PROFILE_FUNCTION();
		m_LayerStack.PushOverlay(layer);
	}

	bool Application::OnWindowClose(WindowCloseEvent & e)
	{
		GES_PROFILE_FUNCTION();
		m_Running = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent & e)
	{
		GES_PROFILE_FUNCTION();
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
