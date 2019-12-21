#include "ges_pch.h"
#include "Texture.h"

#include "GES/Core/Log.h"

#include "RendererSettings.h"

#include "Platform/OpenGL/OpenGLTexture.h"

namespace GES
{
	Ref<Texture2D> Texture2D::Create(cstring source)
	{
		switch(RendererSettings::GetType())
		{
			case RendererSettings::Type::OpenGL:
				return CreateRef<OpenGLTexture2D>(source);
		}
		GES_CORE_ASSERT(false, "unsupported RendererAPI '{0}'", (int32)RendererSettings::GetType());
		return nullptr;
	}
}
