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
		u32 Width;
		u32 Height;

		WindowProps(std::string const & title = "Game Engine Study",
			u32 width = 960,
			u32 height = 540)
			: Title(title), Width(width), Height(height)
		{
		}
	};

	// Interface representing a desktop system based Window
	class GES_DLL Window
	{
	public:
		virtual ~Window() = default;

	public:
		static Scope<Window> Create(WindowProps const & props = WindowProps());

	public:
		virtual void OnUpdate() = 0;

		virtual u32 GetWidth() const = 0;
		virtual u32 GetHeight() const = 0;

		// Window attributes
		using EventCallbackFn = std::function<void(Event&)>;
		virtual void SetEventCallback(EventCallbackFn const & callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		virtual void * GetNativeWindow() const = 0;

	};

}
