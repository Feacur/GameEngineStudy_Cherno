#pragma once
#include "GES/Core.h"

namespace GES
{
	class GES_API GraphicsContext
	{
	public:
		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;
	};
}
