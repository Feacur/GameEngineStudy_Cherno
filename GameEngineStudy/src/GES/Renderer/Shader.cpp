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
	
	std::string FindName(std::string const & source)
	{
		cstring typeToken = "#name";
		const size_t typeTokenLength = strlen(typeToken);

		size_t pos = source.find(typeToken, 0);
		if (pos == std::string::npos) { return ""; }

		size_t eol = source.find_first_of("\r\n", pos);
		GES_CORE_ASSERT(eol != std::string::npos, "Syntax error");

		size_t begin = pos + typeTokenLength + 1;
		return source.substr(begin, eol - begin);
	}

	Shader * Shader::CreatePath(cstring path, cstring name)
	{
		std::string source = ReadFile(path);
		return CreateSource(source.c_str(), name);
	}

	Shader * Shader::CreateSource(cstring source, cstring name)
	{
		std::string autoName;
		if (!name) {
			autoName = FindName(source);
			name = autoName.c_str();
		}
		switch(RendererAPI::GetType())
		{
			case RendererAPI::Type::OpenGL:
				return new OpenGLShader(source, name);
		}
		GES_CORE_ASSERT(false, "unsupported RendererAPI '{0}'", (int32)RendererAPI::GetType());
		return nullptr;
	}

	void ShaderLibrary::Add(Ref<Shader> const & shader) {
		auto & name = shader->GetName();
		m_Shaders[name] = shader;
	}

	Ref<Shader> ShaderLibrary::Get(cstring name) {
		return m_Shaders[name];
	}
}
