#include "ges_pch.h"
#include "RendererCommand.h"

#include "RendererAPI.h"

#include "Platform/OpenGL/OpenGLRendererCommand.h"

namespace GES
{
	RendererCommand * RendererCommand::Create()
	{
		switch(RendererAPI::GetType())
		{
			case RendererAPI::Type::OpenGL:
				return new OpenGLRendererCommand();
		}
		GES_CORE_ASSERT(false, "unsupported RendererAPI '{0}'", (int32)RendererAPI::GetType());
		return nullptr;
	}
}
