#include "ges_pch.h"
#include "VertexArray.h"

#include "GES/Debug/Log.h"
#include "GES/Debug/Instrumentor.h"
#include "GES/Debug/Code.h"

#include "RendererSettings.h"

#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace GES
{
	Ref<VertexArray> VertexArray::Create()
	{
		GES_PROFILE_FUNCTION();
		switch(RendererSettings::GetType())
		{
			case RendererSettings::Type::OpenGL:
				return CreateRef<OpenGLVertexArray>();
		}
		GES_CORE_ASSERT(false, "unsupported RendererAPI '{0}'", (s32)RendererSettings::GetType());
		return nullptr;
	}
}
