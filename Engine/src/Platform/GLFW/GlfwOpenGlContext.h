#pragma once

struct GLFWwindow;

namespace GES
{
	class GlfwOpenGlContext
	{
	public:
		static void Init(GLFWwindow* windowHandle);
	};
}
