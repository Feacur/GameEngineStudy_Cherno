#pragma once

#include "Core.h"

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
