#include "ges_pch.h"
#include "VertexArray.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace GES
{
	VertexArray * VertexArray::Create()
	{
		switch(Renderer::GetAPI())
		{
			case RendererAPI::OpenGL:
				return new OpenGLVertexArray();
		}
		GES_CORE_ASSERT(false, "unsupported RendererAPI '{0}'", (int32)Renderer::GetAPI());
		return nullptr;
	}
}
