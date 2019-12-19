#pragma once
#include "GES/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace GES
{
	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow * windowHandle);

	public:
		void Init() override;
		void SwapBuffers() override;

	private:
		GLFWwindow* m_WindowHandle;
	};
}
