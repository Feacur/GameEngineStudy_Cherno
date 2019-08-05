#include "ges_pch.h"
#include "Shader.h"

#include "RendererAPI.h"

#include "Platform/OpenGL/OpenGLShader.h"

namespace GES
{
	Shader * Shader::Create(cstring vertexSource, cstring fragmentSource)
	{
		switch(RendererAPI::GetType())
		{
			case RendererAPI::Type::OpenGL:
				return new OpenGLShader(vertexSource, fragmentSource);
		}
		GES_CORE_ASSERT(false, "unsupported RendererAPI '{0}'", (int32)RendererAPI::GetType());
		return nullptr;
	}
}
