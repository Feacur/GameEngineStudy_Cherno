#pragma once

#if !defined(GES_BYPASS_VENDOR_HEADERS)
	#include <sstream>
#endif

namespace GES {

	// Events in GES are currently blocking, meaning when an event occurs it
	// immediately gets dispatched and must be dealt with right then an there.
	// For the future, a better strategy might be to buffer events in an event
	// bus and process them during the "event" part of the update stage.

	enum class EventType : s32
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased, KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled,
	};
	UNDERLYING_TYPE_META(EventType, s32)
	IS_ENUM_META(EventType)

	enum class EventCategory : s32
	{
		None           = 0,
		Application    = BIT(s32, 0),
		Input          = BIT(s32, 1),
		Keyboard       = BIT(s32, 2),
		Mouse          = BIT(s32, 3),
		MouseButton    = BIT(s32, 4),
	};
	UNDERLYING_TYPE_META(EventCategory, s32)
	IS_ENUM_META(EventCategory)
	ENUM_FLAG_OPERATORS_IMPL(EventCategory)

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::type; }\
								EventType GetEventType() const override { return GetStaticType(); }\
								cstring GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) EventCategory GetCategoryFlags() const override { return category; }

	class GES_DLL Event
	{
	public:
		bool Handled = false;
	public:
		virtual EventType GetEventType() const = 0;
		virtual cstring GetName() const = 0;
		virtual EventCategory GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }

		inline bool IsInCategory(EventCategory category)
		{
			return bits_are_set(GetCategoryFlags(), category);
		}
	};

	class EventDispatcher
	{
	public:
		EventDispatcher(Event & e)
			: m_Event(e) {}

		template<typename T, typename F>
		bool Dispatch(F const & func)
		{
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				m_Event.Handled = func(static_cast<T&>(m_Event));
				return true;
			}
			return false;
		}
	private:
		Event & m_Event;
	};

	inline std::ostream& operator<<(std::ostream & os, Event const & e)
	{
		return os << e.ToString();
	}
}

