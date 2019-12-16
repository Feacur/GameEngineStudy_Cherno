#pragma once

namespace GES {

	// Events in GES are currently blocking, meaning when an event occurs it
	// immediately gets dispatched and must be dealt with right then an there.
	// For the future, a better strategy might be to buffer events in an event
	// bus and process them during the "event" part of the update stage.

	enum class EventType : int32
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased, KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled,
	};

	enum class EventCategory : int32
	{
		None           = 0,
		Application    = BIT(int32, 0),
		Input          = BIT(int32, 1),
		Keyboard       = BIT(int32, 2),
		Mouse          = BIT(int32, 3),
		MouseButton    = BIT(int32, 4),
	};

	inline EventCategory operator|(EventCategory container, EventCategory bits) {
		return static_cast<EventCategory>(static_cast<int32>(container) | static_cast<int32>(bits));
	}

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::##type; }\
								EventType GetEventType() const override { return GetStaticType(); }\
								cstring GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) int32 GetCategoryFlags() const override { return (int32)(category); }

	class GES_API Event
	{
	public:
		bool Handled = false;
	public:
		virtual EventType GetEventType() const = 0;
		virtual cstring GetName() const = 0;
		virtual int32 GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }

		inline bool IsInCategory(EventCategory category)
		{
			return GetCategoryFlags() & (int32)category;
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

