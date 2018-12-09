#pragma once

#include "Core.h"
#include "Events/Event.h"

namespace GES {
	class GES_API Application
	{
	public:
		Application();
		virtual ~Application();
	public:
		void Run();
	};

	Application *CreateApplication();
}
