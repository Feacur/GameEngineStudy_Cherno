#include "ges_pch.h"
#include "VertexArray.h"

#include "GES/Core/Log.h"

#include "RendererAPI.h"

#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace GES
{
	Ref<VertexArray> VertexArray::Create()
	{
		switch(RendererAPI::GetType())
		{
			case RendererAPI::Type::OpenGL:
				return CreateRef<OpenGLVertexArray>();
		}
		GES_CORE_ASSERT(false, "unsupported RendererAPI '{0}'", (int32)RendererAPI::GetType());
		return nullptr;
	}
}
