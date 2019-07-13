#include "ges_pch.h"
#include "Buffer.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

namespace GES
{
	VertexBuffer * VertexBuffer::Create(float * vertices, uint32 size)
	{
		switch(Renderer::GetAPI())
		{
			case RendererAPI::OpenGL:
				return new OpenGLVertexBuffer(vertices, size);
		}
		GES_CORE_ASSERT(false, "unsupported RendererAPI '{0}'", (int32)Renderer::GetAPI());
		return nullptr;
	}

	IndexBuffer * IndexBuffer::Create(uint32 * indices, uint32 size)
	{
		switch(Renderer::GetAPI())
		{
			case RendererAPI::OpenGL:
				return new OpenGLIndexBuffer(indices, size);
		}
		GES_CORE_ASSERT(false, "unsupported RendererAPI '{0}'", (int32)Renderer::GetAPI());
		return nullptr;
	}
}