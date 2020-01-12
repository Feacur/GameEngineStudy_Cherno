#pragma once
#include "Code.h"

#include "KeyCodes.h"
#include "MouseCodes.h"

namespace GES
{
	// Interface representing a desktop system based Input
	class GES_DLL Input
	{
	public:
		inline static bool IsKeyPressed(KeyCode keycode) { return s_Instance->IsKeyPressedImpl(keycode); }
		inline static bool IsMouseButtonPressed(MouseCode button) { return s_Instance->IsMouseButtonPressedImpl(button); }
		inline static std::pair<r32, r32> GetMousePosition() { return s_Instance->GetMousePositionImpl(); }

	protected:
		virtual bool IsKeyPressedImpl(KeyCode keycode) = 0;
		virtual bool IsMouseButtonPressedImpl(MouseCode button) = 0;
		virtual std::pair<r32, r32> GetMousePositionImpl() = 0;

	private:
		static Scope<Input> s_Instance;
	};
}
