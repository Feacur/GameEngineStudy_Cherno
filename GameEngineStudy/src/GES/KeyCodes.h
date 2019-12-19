#pragma once

namespace GES
{
	typedef enum class KeyCode : uint16
	{
		// From glfw3.h
		Space               = 32,
		Apostrophe          = 39, /* ' */
		Comma               = 44, /* , */
		Minus               = 45, /* - */
		Period              = 46, /* . */
		Slash               = 47, /* / */

		D0                  = 48, /* 0 */
		D1                  = 49, /* 1 */
		D2                  = 50, /* 2 */
		D3                  = 51, /* 3 */
		D4                  = 52, /* 4 */
		D5                  = 53, /* 5 */
		D6                  = 54, /* 6 */
		D7                  = 55, /* 7 */
		D8                  = 56, /* 8 */
		D9                  = 57, /* 9 */

		Semicolon           = 59, /* ; */
		Equal               = 61, /* = */

		A                   = 65,
		B                   = 66,
		C                   = 67,
		D                   = 68,
		E                   = 69,
		F                   = 70,
		G                   = 71,
		H                   = 72,
		I                   = 73,
		J                   = 74,
		K                   = 75,
		L                   = 76,
		M                   = 77,
		N                   = 78,
		O                   = 79,
		P                   = 80,
		Q                   = 81,
		R                   = 82,
		S                   = 83,
		T                   = 84,
		U                   = 85,
		V                   = 86,
		W                   = 87,
		X                   = 88,
		Y                   = 89,
		Z                   = 90,

		LeftBracket         = 91,  /* [ */
		Backslash           = 92,  /* \ */
		RightBracket        = 93,  /* ] */
		GraveAccent         = 96,  /* ` */

		World1              = 161, /* non-US #1 */
		World2              = 162, /* non-US #2 */

		/* Function keys */
		Escape              = 256,
		Enter               = 257,
		Tab                 = 258,
		Backspace           = 259,
		Insert              = 260,
		Delete              = 261,
		Right               = 262,
		Left                = 263,
		Down                = 264,
		Up                  = 265,
		PageUp              = 266,
		PageDown            = 267,
		Home                = 268,
		End                 = 269,
		CapsLock            = 280,
		ScrollLock          = 281,
		NumLock             = 282,
		PrintScreen         = 283,
		Pause               = 284,
		F1                  = 290,
		F2                  = 291,
		F3                  = 292,
		F4                  = 293,
		F5                  = 294,
		F6                  = 295,
		F7                  = 296,
		F8                  = 297,
		F9                  = 298,
		F10                 = 299,
		F11                 = 300,
		F12                 = 301,
		F13                 = 302,
		F14                 = 303,
		F15                 = 304,
		F16                 = 305,
		F17                 = 306,
		F18                 = 307,
		F19                 = 308,
		F20                 = 309,
		F21                 = 310,
		F22                 = 311,
		F23                 = 312,
		F24                 = 313,
		F25                 = 314,

		/* Keypad */
		KP0                 = 320,
		KP1                 = 321,
		KP2                 = 322,
		KP3                 = 323,
		KP4                 = 324,
		KP5                 = 325,
		KP6                 = 326,
		KP7                 = 327,
		KP8                 = 328,
		KP9                 = 329,
		KPDecimal           = 330,
		KPDivide            = 331,
		KPMultiply          = 332,
		KPSubtract          = 333,
		KPAdd               = 334,
		KPEnter             = 335,
		KPEqual             = 336,

		LeftShift           = 340,
		LeftControl         = 341,
		LeftAlt             = 342,
		LeftSuper           = 343,
		RightShift          = 344,
		RightControl        = 345,
		RightAlt            = 346,
		RightSuper          = 347,
		Menu                = 348
	} Key;

	inline std::ostream& operator<<(std::ostream& os, KeyCode keyCode)
	{
		os << static_cast<int32>(keyCode);
		return os;
	}
}

// From glfw3.h
#define GES_KEY_SPACE           ::GES::Key::Space
#define GES_KEY_APOSTROPHE      ::GES::Key::Apostrophe    /* ' */
#define GES_KEY_COMMA           ::GES::Key::Comma         /* , */
#define GES_KEY_MINUS           ::GES::Key::Minus         /* - */
#define GES_KEY_PERIOD          ::GES::Key::Period        /* . */
#define GES_KEY_SLASH           ::GES::Key::Slash         /* / */
#define GES_KEY_0               ::GES::Key::D0
#define GES_KEY_1               ::GES::Key::D1
#define GES_KEY_2               ::GES::Key::D2
#define GES_KEY_3               ::GES::Key::D3
#define GES_KEY_4               ::GES::Key::D4
#define GES_KEY_5               ::GES::Key::D5
#define GES_KEY_6               ::GES::Key::D6
#define GES_KEY_7               ::GES::Key::D7
#define GES_KEY_8               ::GES::Key::D8
#define GES_KEY_9               ::GES::Key::D9
#define GES_KEY_SEMICOLON       ::GES::Key::Semicolon     /* ; */
#define GES_KEY_EQUAL           ::GES::Key::Equal         /* = */
#define GES_KEY_A               ::GES::Key::A
#define GES_KEY_B               ::GES::Key::B
#define GES_KEY_C               ::GES::Key::C
#define GES_KEY_D               ::GES::Key::D
#define GES_KEY_E               ::GES::Key::E
#define GES_KEY_F               ::GES::Key::F
#define GES_KEY_G               ::GES::Key::G
#define GES_KEY_H               ::GES::Key::H
#define GES_KEY_I               ::GES::Key::I
#define GES_KEY_J               ::GES::Key::J
#define GES_KEY_K               ::GES::Key::K
#define GES_KEY_L               ::GES::Key::L
#define GES_KEY_M               ::GES::Key::M
#define GES_KEY_N               ::GES::Key::N
#define GES_KEY_O               ::GES::Key::O
#define GES_KEY_P               ::GES::Key::P
#define GES_KEY_Q               ::GES::Key::Q
#define GES_KEY_R               ::GES::Key::R
#define GES_KEY_S               ::GES::Key::S
#define GES_KEY_T               ::GES::Key::T
#define GES_KEY_U               ::GES::Key::U
#define GES_KEY_V               ::GES::Key::V
#define GES_KEY_W               ::GES::Key::W
#define GES_KEY_X               ::GES::Key::X
#define GES_KEY_Y               ::GES::Key::Y
#define GES_KEY_Z               ::GES::Key::Z
#define GES_KEY_LEFT_BRACKET    ::GES::Key::LeftBracket   /* [ */
#define GES_KEY_BACKSLASH       ::GES::Key::Backslash     /* \ */
#define GES_KEY_RIGHT_BRACKET   ::GES::Key::RightBracket  /* ] */
#define GES_KEY_GRAVE_ACCENT    ::GES::Key::GraveAccent   /* ` */
#define GES_KEY_WORLD_1         ::GES::Key::World1        /* non-US #1 */
#define GES_KEY_WORLD_2         ::GES::Key::World2        /* non-US #2 */

/* Function keys */
#define GES_KEY_ESCAPE          ::GES::Key::Escape
#define GES_KEY_ENTER           ::GES::Key::Enter
#define GES_KEY_TAB             ::GES::Key::Tab
#define GES_KEY_BACKSPACE       ::GES::Key::Backspace
#define GES_KEY_INSERT          ::GES::Key::Insert
#define GES_KEY_DELETE          ::GES::Key::Delete
#define GES_KEY_RIGHT           ::GES::Key::Right
#define GES_KEY_LEFT            ::GES::Key::Left
#define GES_KEY_DOWN            ::GES::Key::Down
#define GES_KEY_UP              ::GES::Key::Up
#define GES_KEY_PAGE_UP         ::GES::Key::PageUp
#define GES_KEY_PAGE_DOWN       ::GES::Key::PageDown
#define GES_KEY_HOME            ::GES::Key::Home
#define GES_KEY_END             ::GES::Key::End
#define GES_KEY_CAPS_LOCK       ::GES::Key::CapsLock
#define GES_KEY_SCROLL_LOCK     ::GES::Key::ScrollLock
#define GES_KEY_NUM_LOCK        ::GES::Key::NumLock
#define GES_KEY_PRINT_SCREEN    ::GES::Key::PrintScreen
#define GES_KEY_PAUSE           ::GES::Key::Pause
#define GES_KEY_F1              ::GES::Key::F1
#define GES_KEY_F2              ::GES::Key::F2
#define GES_KEY_F3              ::GES::Key::F3
#define GES_KEY_F4              ::GES::Key::F4
#define GES_KEY_F5              ::GES::Key::F5
#define GES_KEY_F6              ::GES::Key::F6
#define GES_KEY_F7              ::GES::Key::F7
#define GES_KEY_F8              ::GES::Key::F8
#define GES_KEY_F9              ::GES::Key::F9
#define GES_KEY_F10             ::GES::Key::F10
#define GES_KEY_F11             ::GES::Key::F11
#define GES_KEY_F12             ::GES::Key::F12
#define GES_KEY_F13             ::GES::Key::F13
#define GES_KEY_F14             ::GES::Key::F14
#define GES_KEY_F15             ::GES::Key::F15
#define GES_KEY_F16             ::GES::Key::F16
#define GES_KEY_F17             ::GES::Key::F17
#define GES_KEY_F18             ::GES::Key::F18
#define GES_KEY_F19             ::GES::Key::F19
#define GES_KEY_F20             ::GES::Key::F20
#define GES_KEY_F21             ::GES::Key::F21
#define GES_KEY_F22             ::GES::Key::F22
#define GES_KEY_F23             ::GES::Key::F23
#define GES_KEY_F24             ::GES::Key::F24
#define GES_KEY_F25             ::GES::Key::F25

/* Keypad */
#define GES_KEY_KP_0            ::GES::Key::KP0
#define GES_KEY_KP_1            ::GES::Key::KP1
#define GES_KEY_KP_2            ::GES::Key::KP2
#define GES_KEY_KP_3            ::GES::Key::KP3
#define GES_KEY_KP_4            ::GES::Key::KP4
#define GES_KEY_KP_5            ::GES::Key::KP5
#define GES_KEY_KP_6            ::GES::Key::KP6
#define GES_KEY_KP_7            ::GES::Key::KP7
#define GES_KEY_KP_8            ::GES::Key::KP8
#define GES_KEY_KP_9            ::GES::Key::KP9
#define GES_KEY_KP_DECIMAL      ::GES::Key::KPDecimal
#define GES_KEY_KP_DIVIDE       ::GES::Key::KPDivide
#define GES_KEY_KP_MULTIPLY     ::GES::Key::KPMultiply
#define GES_KEY_KP_SUBTRACT     ::GES::Key::KPSubtract
#define GES_KEY_KP_ADD          ::GES::Key::KPAdd
#define GES_KEY_KP_ENTER        ::GES::Key::KPEnter
#define GES_KEY_KP_EQUAL        ::GES::Key::KPEqual

#define GES_KEY_LEFT_SHIFT      ::GES::Key::LeftShift
#define GES_KEY_LEFT_CONTROL    ::GES::Key::LeftControl
#define GES_KEY_LEFT_ALT        ::GES::Key::LeftAlt
#define GES_KEY_LEFT_SUPER      ::GES::Key::LeftSuper
#define GES_KEY_RIGHT_SHIFT     ::GES::Key::RightShift
#define GES_KEY_RIGHT_CONTROL   ::GES::Key::RightControl
#define GES_KEY_RIGHT_ALT       ::GES::Key::RightAlt
#define GES_KEY_RIGHT_SUPER     ::GES::Key::RightSuper
#define GES_KEY_MENU            ::GES::Key::Menu
