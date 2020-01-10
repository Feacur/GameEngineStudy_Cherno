#pragma once
#include "GES/Core/Input.h"

namespace GES
{
	class WindowsInput : public Input
	{
	protected:
		bool IsKeyPressedImpl(KeyCode keycode) override;
		bool IsMouseButtonPressedImpl(MouseCode button) override;
		std::pair<float, float> GetMousePositionImpl() override;
	};
}
