#include "ges_pch.h"
#include "Shader.h"

#include "GES/Debug/Log.h"
#include "GES/Debug/Instrumentor.h"
#include "GES/Debug/Code.h"

#include "RendererSettings.h"

#include "Platform/OpenGL/OpenGLShader.h"

namespace GES
{
	static std::string ReadFile(cstring path)
	{
		GES_PROFILE_FUNCTION();
		std::ifstream file(path, std::ios::in | std::ios::binary);
		if (!file)
		{
			GES_CORE_ERROR("Could not open file '{0}'", path);
			return "";
		}

		file.seekg(0, std::ios::end);
		size_t size = file.tellg();
		if (size < 0)
		{
			file.close();
			GES_CORE_ERROR("Could not read file '{0}'", path);
			return "";
		}

		std::string result;
		result.resize(file.tellg());
		file.seekg(0, std::ios::beg);

		file.read(&result[0], result.size());
		file.close();
		
		return result;
	}
	
	static std::string FindName(std::string const & source)
	{
		GES_PROFILE_FUNCTION();
		static cstring const token = "// name:";
		static size_t const typeTokenLength = strlen(token);

		size_t pos = source.find(token, 0);
		if (pos == std::string::npos) { return ""; }

		size_t eol = source.find_first_of("\r\n", pos);
		GES_CORE_ASSERT(eol != std::string::npos, "Syntax error");

		size_t begin = pos + typeTokenLength + 1;
		return source.substr(begin, eol - begin);
	}

	Ref<Shader> Shader::CreatePath(cstring path, cstring name)
	{
		GES_PROFILE_FUNCTION();
		std::string source = ReadFile(path);
		return CreateSource(source.c_str(), name);
	}

	Ref<Shader> Shader::CreateSource(cstring source, cstring name)
	{
		GES_PROFILE_FUNCTION();
		std::string autoName;
		if (!name) {
			autoName = FindName(source);
			name = autoName.c_str();
		}
		switch(RendererSettings::GetType())
		{
			case RendererSettings::Type::OpenGL:
				return CreateRef<OpenGLShader>(source, name);
		}
		GES_CORE_ASSERT(false, "unsupported RendererAPI '{0}'", (s32)RendererSettings::GetType());
		return nullptr;
	}

	void ShaderLibrary::Add(Ref<Shader> const & shader) {
		GES_PROFILE_FUNCTION();
		std::string const & name = shader->GetName();
		m_Shaders[name] = shader;
	}

	Ref<Shader> ShaderLibrary::Get(cstring name) {
		GES_PROFILE_FUNCTION();
		return m_Shaders[name];
	}
}
