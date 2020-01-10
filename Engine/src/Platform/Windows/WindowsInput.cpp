#include "ges_pch.h"
// #include "GES/Core/KeyCodes.h"
// #include "GES/Core/MouseCodes.h"
#include "WindowsInput.h"

#include "GES/Core/Window.h"
#include "GES/Core/Application.h"

#include "GES/Debug/Instrumentor.h"
#include "GES/Debug/Code.h"

#include <GLFW/glfw3.h>

namespace GES
{
	Scope<Input> Input::s_Instance = CreateScope<WindowsInput>();

	bool WindowsInput::IsKeyPressedImpl(KeyCode keycode)
	{
		GES_PROFILE_FUNCTION();
		auto window = static_cast<GLFWwindow *>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetKey(window, static_cast<int32>(keycode));
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool WindowsInput::IsMouseButtonPressedImpl(MouseCode button)
	{
		GES_PROFILE_FUNCTION();
		auto window = static_cast<GLFWwindow *>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetMouseButton(window, static_cast<int32>(button));
		return state == GLFW_PRESS;
	}

	std::pair<float, float> WindowsInput::GetMousePositionImpl()
	{
		GES_PROFILE_FUNCTION();
		auto window = static_cast<GLFWwindow *>(Application::Get().GetWindow().GetNativeWindow());
		double x, y;
		glfwGetCursorPos(window, &x, &y);
		return {(float)x, (float)y};
	}
}
