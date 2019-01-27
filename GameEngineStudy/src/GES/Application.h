#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "Window.h"

namespace GES {
	GES_TEMPLATE template class GES_API std::_Compressed_pair<std::default_delete<Window>, Window *, true>;
	GES_TEMPLATE template class GES_API std::unique_ptr<Window>;

	class GES_API Application
	{
	public:
		Application();
		virtual ~Application();
	public:
		void Run();
	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
	};

	Application *CreateApplication();
}
