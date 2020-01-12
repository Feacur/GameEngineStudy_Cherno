#include "ges_pch.h"
#include "GraphicsContext.h"

#include "GES/Debug/Log.h"
#include "GES/Debug/Instrumentor.h"
#include "GES/Debug/Code.h"

#include "RendererSettings.h"

#include "Platform/OpenGL/OpenGLContext.h"

namespace GES
{
	Scope<GraphicsContext> GraphicsContext::Create(void * windowHandle)
	{
		GES_PROFILE_FUNCTION();
		switch(RendererSettings::GetType())
		{
			case RendererSettings::Type::OpenGL:
				return CreateScope<OpenGLContext>(static_cast<GLFWwindow*>(windowHandle));
		}
		GES_CORE_ASSERT(false, "unsupported RendererAPI '{0}'", (s32)RendererSettings::GetType());
		return nullptr;
	}
}
