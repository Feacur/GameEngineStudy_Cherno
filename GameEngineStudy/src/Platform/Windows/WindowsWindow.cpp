#include "ges_pch.h"
#include "WindowsWindow.h"

#include "GES/Debug/Log.h"
#include "GES/Debug/Instrumentor.h"
#include "GES/Debug/Code.h"

extern "C" { // @Note: use discrete GPU by default
	// http://developer.download.nvidia.com/devzone/devcenter/gamegraphics/files/OptimusRenderingPolicies.pdf
	GES_API_EXPORT DWORD NvOptimusEnablement = 1;
	// https://community.amd.com/thread/223376
	// https://gpuopen.com/amdpowerxpressrequesthighperformance/
	GES_API_EXPORT DWORD AmdPowerXpressRequestHighPerformance = 1;
}

#include "GES/Core/KeyCodes.h"
#include "GES/Core/MouseCodes.h"

#include "GES/Events/Event.h"
#include "GES/Events/ApplicationEvent.h"
#include "GES/Events/MouseEvent.h"
#include "GES/Events/KeyEvent.h"

#include "GES/Renderer/RendererSettings.h"
#include "GES/Renderer/GraphicsContext.h"

#include <GLFW/glfw3.h>

namespace GES {
	static uint8 s_GLFWWindowCount = 0;

	static void GLFWErrorCallback(int error, cstring description)
	{
		GES_PROFILE_FUNCTION();
		GES_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
	}

	Scope<Window> Window::Create(WindowProps const & props)
	{
		GES_PROFILE_FUNCTION();
		return CreateScope<WindowsWindow>(props);
	}

	WindowsWindow::WindowsWindow(WindowProps const & props)
	{
		GES_PROFILE_FUNCTION();
		Init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		GES_PROFILE_FUNCTION();
		Shutdown();
	}

	void WindowsWindow::Init(WindowProps const & props)
	{
		GES_PROFILE_FUNCTION();
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		GES_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width, props.Height);

		if (s_GLFWWindowCount == 0)
		{
			GES_CORE_INFO("Initializing GLFW");
			int success = glfwInit();
			GES_CORE_ASSERT(success, "Could not intialize GLFW!");

			glfwSetErrorCallback(&GLFWErrorCallback);
		}

		#if !defined(GES_SHIPPING)
		if (RendererSettings::GetType() == RendererSettings::Type::OpenGL)
		{
			glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
		}
		#endif
		m_WindowHandle = glfwCreateWindow((int32)props.Width, (int32)props.Height, m_Data.Title.c_str(), nullptr, nullptr);
		++s_GLFWWindowCount;

		m_Context = GraphicsContext::Create(m_WindowHandle);
		m_Context->Init();

		glfwSetWindowUserPointer(m_WindowHandle, &m_Data);
		SetVSync(true);

		glfwSetWindowSizeCallback(m_WindowHandle, [](GLFWwindow * window, int32 width, int32 height) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			data.Width = width;
			data.Height = height;

			WindowResizeEvent event(width, height);
			data.EventCallback(event);
		});

		glfwSetWindowCloseCallback(m_WindowHandle, [](GLFWwindow * window) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			WindowCloseEvent event;
			data.EventCallback(event);
		});

		glfwSetKeyCallback(m_WindowHandle, [](GLFWwindow * window, int32 key, int32 scancode, int32 action, int32 mods) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action) {
				case GLFW_PRESS: {
					KeyPressedEvent event(static_cast<KeyCode>(key), 0);
					data.EventCallback(event);
				} break;
				case GLFW_RELEASE: {
					KeyReleasedEvent event(static_cast<KeyCode>(key));
					data.EventCallback(event);
				} break;
				case GLFW_REPEAT: {
					KeyPressedEvent event(static_cast<KeyCode>(key), 1);
					data.EventCallback(event);
				} break;
			}
		});

		glfwSetCharCallback(m_WindowHandle, [](GLFWwindow * window, uint32 keycode) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			KeyTypedEvent event(static_cast<KeyCode>(keycode));
			data.EventCallback(event);
		});

		glfwSetMouseButtonCallback(m_WindowHandle, [](GLFWwindow * window, int button, int action, int mods) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			
			switch (action) {
				case GLFW_PRESS: {
					MouseButtonPressedEvent event(static_cast<MouseCode>(button));
					data.EventCallback(event);
				} break;
				case GLFW_RELEASE: {
					MouseButtonReleasedEvent event(static_cast<MouseCode>(button));
					data.EventCallback(event);
				} break;
			}
		});

		glfwSetScrollCallback(m_WindowHandle, [](GLFWwindow * window, double xOffset, double yOffset) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseScrolledEvent event((float)xOffset, (float)yOffset);
			data.EventCallback(event);
		});

		glfwSetCursorPosCallback(m_WindowHandle, [](GLFWwindow * window, double xPos, double yPos) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseMovedEvent event((float)xPos, (float)yPos);
			data.EventCallback(event);
		});
	}

	void WindowsWindow::Shutdown()
	{
		GES_PROFILE_FUNCTION();
		glfwDestroyWindow(m_WindowHandle);
		--s_GLFWWindowCount;
		if (s_GLFWWindowCount == 0) {
			GES_CORE_INFO("Terminating GLFW");
			glfwTerminate();
		}
	}

	void WindowsWindow::OnUpdate()
	{
		GES_PROFILE_FUNCTION();
		glfwPollEvents();
		m_Context->SwapBuffers();
	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		GES_PROFILE_FUNCTION();
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_Data.VSync = enabled;
	}

	bool WindowsWindow::IsVSync() const
	{
		GES_PROFILE_FUNCTION();
		return m_Data.VSync;
	}
}
