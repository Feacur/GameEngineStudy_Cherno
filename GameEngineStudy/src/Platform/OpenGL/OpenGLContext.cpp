#include "ges_pch.h"
#include "OpenGLContext.h"

#include "GES/Log.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace GES
{
	OpenGLContext::OpenGLContext(GLFWwindow * windowHandle)
		: m_WindowHandle(windowHandle)
	{
		GES_CORE_ASSERT(windowHandle, "Window handle is null");
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int gladStatus = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		GES_CORE_ASSERT(gladStatus, "Failed to initialize Glad");

		GES_CORE_INFO("OpenGL Info:");
		GES_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
		GES_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
		GES_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));
		
		// int versionMajor;
		// int versionMinor;
		// glGetIntegerv(GL_MAJOR_VERSION, &versionMajor);
		// glGetIntegerv(GL_MINOR_VERSION, &versionMinor);
		// GES_CORE_ASSERT(versionMajor > 4 || (versionMajor == 4 && versionMinor >= 5), "GES requires at least OpenGL version 4.5!");
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}
