#include "ges_pch.h"
#include "OpenGLContext.h"

#include "GES/Debug/Log.h"
#include "GES/Debug/Instrumentor.h"
#include "GES/Debug/Code.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace GES
{
	void OpenGLContext::Init(GLFWwindow * windowHandle)
	{
		GES_PROFILE_FUNCTION();
		glfwMakeContextCurrent(windowHandle);
		int gladStatus = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		GES_CORE_ASSERT(gladStatus, "Failed to initialize Glad");

		GES_CORE_INFO("OpenGL Info:");
		GES_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
		GES_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
		GES_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));
		
		// GLint versionMajor;
		// glGetIntegerv(GL_MAJOR_VERSION, &versionMajor);
		// GLint versionMinor;
		// glGetIntegerv(GL_MINOR_VERSION, &versionMinor);
		// GES_CORE_ASSERT(versionMajor > 4 || (versionMajor == 4 && versionMinor >= 5), "GES requires at least OpenGL version 4.5!");
	}
}
