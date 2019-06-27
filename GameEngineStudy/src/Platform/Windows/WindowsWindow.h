#pragma once

#include "GES/Window.h"

#include <GLFW/glfw3.h>

namespace GES {
	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(WindowProps const & props);
		~WindowsWindow() override;

		void OnUpdate() override;

		inline uint32 GetWidth() const override { return m_Data.Width; }
		inline uint32 GetHeight() const override { return m_Data.Height; }

		// Window attributes
		inline void SetEventCallback(EventCallbackFn const & callback) override { m_Data.EventCallback = callback; }
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;
		inline void * GetNativeWindow() const override { return m_Window; }
	private:
		void Init(WindowProps const & props);
		void Shutdown();
	private:
		GLFWwindow* m_Window;

		struct WindowData
		{
			std::string Title;
			uint32 Width, Height;
			bool VSync;

			EventCallbackFn EventCallback;
		};

		WindowData m_Data;
	};

}
