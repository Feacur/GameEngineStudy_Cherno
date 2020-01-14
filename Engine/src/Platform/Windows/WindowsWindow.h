#pragma once
#include "GES/Core/Window.h"

struct GLFWwindow;

namespace GES {
	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(WindowProps const & props);
		~WindowsWindow() override;

		void OnUpdate() override;

		inline u32 GetWidth() const override { return m_Data.Width; }
		inline u32 GetHeight() const override { return m_Data.Height; }

		// Window attributes
		inline void SetEventCallback(EventCallbackFn const & callback) override { m_Data.EventCallback = callback; }
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;
		inline void * GetNativeWindow() const override { return m_WindowHandle; }
	private:
		void Init(WindowProps const & props);
		void Shutdown();
	private:
		GLFWwindow* m_WindowHandle;

		struct WindowData
		{
			std::string Title;
			u32 Width, Height;
			bool VSync;

			EventCallbackFn EventCallback;
		};

		WindowData m_Data;
	};

}
