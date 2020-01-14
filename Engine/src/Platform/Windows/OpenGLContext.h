#pragma once

struct GLFWwindow;

namespace GES
{
	class OpenGLContext
	{
	public:
		static void Init(GLFWwindow* windowHandle);
	};
}
