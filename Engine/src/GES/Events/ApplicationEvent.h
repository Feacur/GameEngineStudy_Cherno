#pragma once

// #include "Core/Event.h"

namespace GES {

	class GES_DLL WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(u32 width, u32 height)
			: m_Width(width), m_Height(height) {}

		inline u32 GetWidth() const { return m_Width; }
		inline u32 GetHeight() const { return m_Height; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowResizeEvent: " << m_Width << ", " << m_Height;
			return ss.str();
		}

		EVENT_CLASS_TYPE(WindowResize)
		EVENT_CLASS_CATEGORY(EventCategory::Application)
	private:
		u32 m_Width, m_Height;
	};

	class GES_DLL WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent() = default;

		EVENT_CLASS_TYPE(WindowClose)
		EVENT_CLASS_CATEGORY(EventCategory::Application)
	};

	class GES_DLL AppTickEvent : public Event
	{
	public:
		AppTickEvent() = default;

		EVENT_CLASS_TYPE(AppTick)
		EVENT_CLASS_CATEGORY(EventCategory::Application)
	};

	class GES_DLL AppUpdateEvent : public Event
	{
	public:
		AppUpdateEvent() = default;

		EVENT_CLASS_TYPE(AppUpdate)
		EVENT_CLASS_CATEGORY(EventCategory::Application)
	};

	class GES_DLL AppRenderEvent : public Event
	{
	public:
		AppRenderEvent() = default;

		EVENT_CLASS_TYPE(AppRender)
		EVENT_CLASS_CATEGORY(EventCategory::Application)
	};
}