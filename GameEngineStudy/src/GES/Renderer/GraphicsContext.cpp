#include "ges_pch.h"
#include "GraphicsContext.h"

#include "GES/Debug/Log.h"

#include "RendererSettings.h"

#include "Platform/OpenGL/OpenGLContext.h"

namespace GES
{
	Scope<GraphicsContext> GraphicsContext::Create(void * windowHandle)
	{
		switch(RendererSettings::GetType())
		{
			case RendererSettings::Type::OpenGL:
				return CreateScope<OpenGLContext>(static_cast<GLFWwindow*>(windowHandle));
		}
		GES_CORE_ASSERT(false, "unsupported RendererAPI '{0}'", (int32)RendererSettings::GetType());
		return nullptr;
	}
}
