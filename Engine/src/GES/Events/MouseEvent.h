#pragma once

// #include "Event.h"
// #include "GES/Core/MouseCodes.h"

namespace GES {

	class GES_DLL MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(r32 x, r32 y)
			: m_MouseX(x), m_MouseY(y) {}

		inline r32 GetX() const { return m_MouseX; }
		inline r32 GetY() const { return m_MouseY; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseMovedEvent: " << m_MouseX << ", " << m_MouseY;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseMoved)
		EVENT_CLASS_CATEGORY(EventCategory::Mouse | EventCategory::Input)
	private:
		r32 m_MouseX, m_MouseY;
	};

	class GES_DLL MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(r32 xOffset, r32 yOffset)
			: m_XOffset(xOffset), m_YOffset(yOffset) {}

		inline r32 GetXOffset() const { return m_XOffset; }
		inline r32 GetYOffset() const { return m_YOffset; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseScrolledEvent: " << GetXOffset() << ", " << GetYOffset();
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseScrolled)
		EVENT_CLASS_CATEGORY(EventCategory::Mouse | EventCategory::Input)
	private:
		r32 m_XOffset, m_YOffset;
	};

	class GES_DLL MouseButtonEvent : public Event
	{
	public:
		inline MouseCode GetMouseButton() const { return m_Button; }

		EVENT_CLASS_CATEGORY(EventCategory::Mouse | EventCategory::Input)
	protected:
		MouseButtonEvent(MouseCode button)
			: m_Button(button) {}

		MouseCode m_Button;
	};

	class GES_DLL MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(MouseCode button)
			: MouseButtonEvent(button) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << m_Button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonPressed)
	};

	class GES_DLL MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(MouseCode button)
			: MouseButtonEvent(button) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent: " << m_Button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonReleased)
	};

}
