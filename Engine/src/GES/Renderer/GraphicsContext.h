#pragma once
#include "GES/Core/Code.h"

namespace GES
{
	class GES_DLL GraphicsContext
	{
	public:
		static Scope<GraphicsContext> Create(void * windowHandle);

	public:
		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;
	};
}
