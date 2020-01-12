#include "ges_pch.h"
#include "Texture.h"

#include "GES/Debug/Log.h"
#include "GES/Debug/Instrumentor.h"
#include "GES/Debug/Code.h"

#include "RendererSettings.h"

#include "Platform/OpenGL/OpenGLTexture.h"

namespace GES
{
	Ref<Texture2D> Texture2D::CreateRaw(u32 width, u32 height)
	{
		GES_PROFILE_FUNCTION();
		switch(RendererSettings::GetType())
		{
			case RendererSettings::Type::OpenGL:
				return CreateRef<OpenGLTexture2D>(width, height);
		}
		GES_CORE_ASSERT(false, "unsupported RendererAPI '{0}'", (s32)RendererSettings::GetType());
		return nullptr;
	}
	
	Ref<Texture2D> Texture2D::CreatePath(cstring source)
	{
		GES_PROFILE_FUNCTION();
		switch(RendererSettings::GetType())
		{
			case RendererSettings::Type::OpenGL:
				return CreateRef<OpenGLTexture2D>(source);
		}
		GES_CORE_ASSERT(false, "unsupported RendererAPI '{0}'", (s32)RendererSettings::GetType());
		return nullptr;
	}
}
