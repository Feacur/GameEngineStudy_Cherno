#include "ges_pch.h"
#include "RendererCommand.h"

#include "GES/Core/Log.h"

#include "RendererSettings.h"

#include "Platform/OpenGL/OpenGLRendererCommand.h"

namespace GES
{
	Scope<RendererCommand> RendererCommand::Create()
	{
		switch(RendererSettings::GetType())
		{
			case RendererSettings::Type::OpenGL:
				return CreateScope<OpenGLRendererCommand>();
		}
		GES_CORE_ASSERT(false, "unsupported RendererAPI '{0}'", (int32)RendererSettings::GetType());
		return nullptr;
	}
}
