#include "ges_pch.h"
#include "Buffer.h"

#include "GES/Core/Log.h"

#include "RendererSettings.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

namespace GES
{
	Ref<VertexBuffer> VertexBuffer::Create(float * vertices, uint32 size)
	{
		switch(RendererSettings::GetType())
		{
			case RendererSettings::Type::OpenGL:
				return CreateRef<OpenGLVertexBuffer>(vertices, size);
		}
		GES_CORE_ASSERT(false, "unsupported RendererAPI '{0}'", (int32)RendererSettings::GetType());
		return nullptr;
	}

	Ref<IndexBuffer> IndexBuffer::Create(uint32 * indices, uint32 size)
	{
		switch(RendererSettings::GetType())
		{
			case RendererSettings::Type::OpenGL:
				return CreateRef<OpenGLIndexBuffer>(indices, size);
		}
		GES_CORE_ASSERT(false, "unsupported RendererAPI '{0}'", (int32)RendererSettings::GetType());
		return nullptr;
	}
}