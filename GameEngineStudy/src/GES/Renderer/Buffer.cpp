#include "ges_pch.h"
#include "Buffer.h"

#include "GES/Log.h"

#include "RendererAPI.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

namespace GES
{
	Ref<VertexBuffer> VertexBuffer::Create(float * vertices, uint32 size)
	{
		switch(RendererAPI::GetType())
		{
			case RendererAPI::Type::OpenGL:
				return CreateRef<OpenGLVertexBuffer>(vertices, size);
		}
		GES_CORE_ASSERT(false, "unsupported RendererAPI '{0}'", (int32)RendererAPI::GetType());
		return nullptr;
	}

	Ref<IndexBuffer> IndexBuffer::Create(uint32 * indices, uint32 size)
	{
		switch(RendererAPI::GetType())
		{
			case RendererAPI::Type::OpenGL:
				return CreateRef<OpenGLIndexBuffer>(indices, size);
		}
		GES_CORE_ASSERT(false, "unsupported RendererAPI '{0}'", (int32)RendererAPI::GetType());
		return nullptr;
	}
}