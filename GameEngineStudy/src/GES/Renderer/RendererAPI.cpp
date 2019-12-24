#include "ges_pch.h"
#include "RendererAPI.h"

#include "GES/Debug/Log.h"
#include "GES/Debug/Instrumentor.h"
#include "GES/Debug/Code.h"

#include "RendererSettings.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace GES
{
	Scope<RendererAPI> RendererAPI::Create()
	{
		GES_PROFILE_FUNCTION();
		switch(RendererSettings::GetType())
		{
			case RendererSettings::Type::OpenGL:
				return CreateScope<OpenGLRendererAPI>();
		}
		GES_CORE_ASSERT(false, "unsupported RendererAPI '{0}'", (int32)RendererSettings::GetType());
		return nullptr;
	}
}
