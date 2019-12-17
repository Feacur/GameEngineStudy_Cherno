#include "ges_pch.h"
#include "Shader.h"

#include "RendererAPI.h"

#include "Platform/OpenGL/OpenGLShader.h"

#include <fstream>

namespace GES
{
	std::string ReadFile(cstring path)
	{
		std::ifstream file(path, std::ios::in | std::ios::binary);
		if (!file)
		{
			GES_CORE_ERROR("Could not open file '{0}'", path);
			return "";
		}

		std::string result;
		file.seekg(0, std::ios::end);
		result.resize(file.tellg());
		file.seekg(0, std::ios::beg);

		file.read(&result[0], result.size());
		file.close();
		
		return result;
	}

	Shader * Shader::CreatePath(cstring path)
	{
		std::string source = ReadFile(path);
		return CreateSource(source.c_str());
	}

	Shader * Shader::CreateSource(cstring source)
	{
		switch(RendererAPI::GetType())
		{
			case RendererAPI::Type::OpenGL:
				return new OpenGLShader(source);
		}
		GES_CORE_ASSERT(false, "unsupported RendererAPI '{0}'", (int32)RendererAPI::GetType());
		return nullptr;
	}
}
