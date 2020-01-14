#include "ges_pch.h"
#include "Window.h"

#include "GES/Debug/Log.h"
#include "GES/Debug/Instrumentor.h"
#include "GES/Debug/Code.h"

#include "Platform/GLFW/GlfwWindow.h"

namespace GES
{
	Scope<Window> Window::Create(WindowProps const & props)
	{
		GES_PROFILE_FUNCTION();
		return CreateScope<GlfwWindow>(props);
	}
}
