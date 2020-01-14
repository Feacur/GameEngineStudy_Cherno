#pragma once
#include "GES/Core/Input.h"

namespace GES
{
	class GlfwInput : public Input
	{
	public:
		GlfwInput();
		~GlfwInput() override = default;

	protected:
		bool IsKeyPressedImpl(KeyCode keycode) override;
		bool IsMouseButtonPressedImpl(MouseCode button) override;
		std::pair<float, float> GetMousePositionImpl() override;
	};
}
