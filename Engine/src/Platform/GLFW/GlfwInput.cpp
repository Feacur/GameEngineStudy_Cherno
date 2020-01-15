#include "ges_pch.h"
// #include "GES/Core/KeyCodes.h"
// #include "GES/Core/MouseCodes.h"
#include "GlfwInput.h"

#include "GES/Debug/Instrumentor.h"
#include "GES/Debug/Code.h"

#include <GLFW/glfw3.h>

namespace GES
{
	GlfwInput::GlfwInput()
	{
		GES_PROFILE_FUNCTION();
		s_Instance = this;
	}

	bool GlfwInput::IsKeyPressedImpl(KeyCode keycode)
	{
		GES_PROFILE_FUNCTION();
		GLFWwindow * window = glfwGetCurrentContext();
		int state = glfwGetKey(window, static_cast<s32>(keycode));
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool GlfwInput::IsMouseButtonPressedImpl(MouseCode button)
	{
		GES_PROFILE_FUNCTION();
		GLFWwindow * window = glfwGetCurrentContext();
		int state = glfwGetMouseButton(window, static_cast<s32>(button));
		return state == GLFW_PRESS;
	}

	std::pair<float, float> GlfwInput::GetMousePositionImpl()
	{
		GES_PROFILE_FUNCTION();
		GLFWwindow * window = glfwGetCurrentContext();
		double x, y;
		glfwGetCursorPos(window, &x, &y);
		return {(float)x, (float)y};
	}
}
