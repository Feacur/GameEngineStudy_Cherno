#include "ges_pch.h"
// #include "GES/Core/KeyCodes.h"
// #include "GES/Core/MouseCodes.h"
#include "GlfwInput.h"

#include "GES/Core/Window.h"
#include "GES/Core/Application.h"

#include "GES/Debug/Instrumentor.h"
#include "GES/Debug/Code.h"

#include <GLFW/glfw3.h>

namespace GES
{
	GlfwInput::GlfwInput()
	{
		s_Instance = this;
	}

	bool GlfwInput::IsKeyPressedImpl(KeyCode keycode)
	{
		GES_PROFILE_FUNCTION();
		auto window = static_cast<GLFWwindow *>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetKey(window, static_cast<s32>(keycode));
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool GlfwInput::IsMouseButtonPressedImpl(MouseCode button)
	{
		GES_PROFILE_FUNCTION();
		auto window = static_cast<GLFWwindow *>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetMouseButton(window, static_cast<s32>(button));
		return state == GLFW_PRESS;
	}

	std::pair<float, float> GlfwInput::GetMousePositionImpl()
	{
		GES_PROFILE_FUNCTION();
		auto window = static_cast<GLFWwindow *>(Application::Get().GetWindow().GetNativeWindow());
		double x, y;
		glfwGetCursorPos(window, &x, &y);
		return {(float)x, (float)y};
	}
}
