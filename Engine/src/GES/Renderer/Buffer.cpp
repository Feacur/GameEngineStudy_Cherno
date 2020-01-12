#include "ges_pch.h"
#include "Buffer.h"

#include "GES/Debug/Log.h"
#include "GES/Debug/Instrumentor.h"
#include "GES/Debug/Code.h"

#include "RendererSettings.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

namespace GES
{
	Ref<VertexBuffer> VertexBuffer::Create(r32 * vertices, u32 count)
	{
		GES_PROFILE_FUNCTION();
		switch(RendererSettings::GetType())
		{
			case RendererSettings::Type::OpenGL:
				return CreateRef<OpenGLVertexBuffer>(vertices, count);
		}
		GES_CORE_ASSERT(false, "unsupported RendererAPI '{0}'", (s32)RendererSettings::GetType());
		return nullptr;
	}

	Ref<IndexBuffer> IndexBuffer::Create(u32 * indices, u32 count)
	{
		GES_PROFILE_FUNCTION();
		switch(RendererSettings::GetType())
		{
			case RendererSettings::Type::OpenGL:
				return CreateRef<OpenGLIndexBuffer>(indices, count);
		}
		GES_CORE_ASSERT(false, "unsupported RendererAPI '{0}'", (s32)RendererSettings::GetType());
		return nullptr;
	}
}