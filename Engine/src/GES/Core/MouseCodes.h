#pragma once

namespace GES
{
	typedef enum class MouseCode : u16
	{
		// From glfw3.h
		Button0                = 0,
		Button1                = 1,
		Button2                = 2,
		Button3                = 3,
		Button4                = 4,
		Button5                = 5,
		Button6                = 6,
		Button7                = 7,

		ButtonLast             = Button7,
		ButtonLeft             = Button0,
		ButtonRight            = Button1,
		ButtonMiddle           = Button2
	} Mouse;
	
	inline std::ostream& operator<<(std::ostream& os, MouseCode mouseCode)
	{
		os << static_cast<s32>(mouseCode);
		return os;
	}
}

#define GES_MOUSE_BUTTON_0      ::GES::Mouse::Button0
#define GES_MOUSE_BUTTON_1      ::GES::Mouse::Button1
#define GES_MOUSE_BUTTON_2      ::GES::Mouse::Button2
#define GES_MOUSE_BUTTON_3      ::GES::Mouse::Button3
#define GES_MOUSE_BUTTON_4      ::GES::Mouse::Button4
#define GES_MOUSE_BUTTON_5      ::GES::Mouse::Button5
#define GES_MOUSE_BUTTON_6      ::GES::Mouse::Button6
#define GES_MOUSE_BUTTON_7      ::GES::Mouse::Button7
#define GES_MOUSE_BUTTON_LAST   ::GES::Mouse::ButtonLast
#define GES_MOUSE_BUTTON_LEFT   ::GES::Mouse::ButtonLeft
#define GES_MOUSE_BUTTON_RIGHT  ::GES::Mouse::ButtonRight
#define GES_MOUSE_BUTTON_MIDDLE ::GES::Mouse::ButtonMiddle
