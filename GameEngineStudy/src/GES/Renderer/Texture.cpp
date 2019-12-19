#include "ges_pch.h"
#include "Texture.h"

#include "GES/Log.h"

#include "RendererAPI.h"

#include "Platform/OpenGL/OpenGLTexture.h"

namespace GES
{
	Ref<Texture2D> Texture2D::Create(cstring source)
	{
		switch(RendererAPI::GetType())
		{
			case RendererAPI::Type::OpenGL:
				return CreateRef<OpenGLTexture2D>(source);
		}
		GES_CORE_ASSERT(false, "unsupported RendererAPI '{0}'", (int32)RendererAPI::GetType());
		return nullptr;
	}
}
