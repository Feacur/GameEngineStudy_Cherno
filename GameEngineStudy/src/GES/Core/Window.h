#pragma once
#include "GES/Core/Code.h"

#if !defined(GES_BYPASS_VENDOR_HEADERS)
	#include <string>
	#include <functional>
#endif

namespace GES {
	class Event;

	struct WindowProps
	{
		std::string Title;
		uint32 Width;
		uint32 Height;

		WindowProps(std::string const & title = "Game Engine Study",
			uint32 width = 960,
			uint32 height = 540)
			: Title(title), Width(width), Height(height)
		{
		}
	};

	// Interface representing a desktop system based Window
	class GES_API Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() = default;

		virtual void OnUpdate() = 0;

		virtual uint32 GetWidth() const = 0;
		virtual uint32 GetHeight() const = 0;

		// Window attributes
		virtual void SetEventCallback(EventCallbackFn const & callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		virtual void * GetNativeWindow() const = 0;

		static Scope<Window> Create(WindowProps const & props = WindowProps());
	};

}
