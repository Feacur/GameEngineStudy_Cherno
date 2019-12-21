#include "ges_pch.h"
#include "GraphicsContext.h"

#include "GES/Core/Log.h"

#include "RendererAPI.h"

#include "Platform/OpenGL/OpenGLContext.h"

namespace GES
{
	Scope<GraphicsContext> GraphicsContext::Create(void * windowHandle)
	{
		switch(RendererAPI::GetType())
		{
			case RendererAPI::Type::OpenGL:
				return CreateScope<OpenGLContext>(static_cast<GLFWwindow*>(windowHandle));
		}
		GES_CORE_ASSERT(false, "unsupported RendererAPI '{0}'", (int32)RendererAPI::GetType());
		return nullptr;
	}
}
