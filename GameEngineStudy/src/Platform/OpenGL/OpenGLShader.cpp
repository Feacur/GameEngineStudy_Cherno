#include "ges_pch.h"
#include "OpenGLShader.h"

#include "GES/Core/Log.h"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

#include <unordered_map>

typedef GLchar const * glstring;

namespace GES
{
	static GLenum ShaderTypeFromString(std::string const & type)
	{
		if (type == "vertex") {
			return GL_VERTEX_SHADER;
		}

		if (type == "fragment" || type == "pixel") {
			return GL_FRAGMENT_SHADER;
		}

		GES_CORE_ASSERT(false, "Unknown shader type");
		return 0;
	}

	std::unordered_map<GLenum, std::string> PreProcess(std::string const & source)
	{
		std::unordered_map<GLenum, std::string> shaderSources;

		cstring typeToken = "#type";
		const size_t typeTokenLength = strlen(typeToken);
		
		size_t pos = source.find(typeToken, 0);
		while (pos != std::string::npos)
		{
			size_t eol = source.find_first_of("\r\n", pos);
			GES_CORE_ASSERT(eol != std::string::npos, "Syntax error");

			size_t begin = pos + typeTokenLength + 1;
			std::string type = source.substr(begin, eol - begin);

			size_t nextLinePos = source.find_first_not_of("\r\n", eol);
			GES_CORE_ASSERT(nextLinePos != std::string::npos, "Syntax error");

			pos = source.find(typeToken, nextLinePos);
			shaderSources[ShaderTypeFromString(type)] = (pos == std::string::npos) ? source.substr(nextLinePos) : source.substr(nextLinePos, pos - nextLinePos);
		}

		return shaderSources;
	}

	GLuint Compile(const std::unordered_map<GLenum, std::string>& shaderSources)
	{
		GLuint program = glCreateProgram();
		GLenum glShaderIDs[4] = {};
		uint8 glShaderIDsIndex = 0;
		for (auto& kv : shaderSources)
		{
			GLenum type = kv.first;
			GLuint shader = glCreateShader(type);

			std::string const & source = kv.second;
			glstring sourceCStr = source.c_str();

			glShaderSource(shader, 1, &sourceCStr, 0);
			glCompileShader(shader);

			GLint isCompiled = 0;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
			if (isCompiled == GL_FALSE)
			{
				GLint maxLength = 0;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

				std::vector<GLchar> infoLog(maxLength);
				glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

				glDeleteShader(shader);

				GES_CORE_ERROR("{0}", infoLog.data());
				GES_CORE_ASSERT(false, "Shader compilation failure!");
				break;
			}

			glAttachShader(program, shader);
			glShaderIDs[glShaderIDsIndex++] = shader;
		}

		// Link our program
		glLinkProgram(program);
		for (uint8 i = 0; i < glShaderIDsIndex; i++) {
			glDetachShader(program, glShaderIDs[i]);
			glDeleteShader(glShaderIDs[i]);
		}

		// Note the different functions here: glGetProgram* instead of glGetShader*.
		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

			glDeleteProgram(program);
			
			GES_CORE_ERROR("{0}", infoLog.data());
			GES_CORE_ASSERT(false, "Shader link failure!");
			return 0;
		}

		return program;
	}

	OpenGLShader::OpenGLShader(cstring source, cstring name)
	{
		auto shaderSources = PreProcess(source);
		m_RendererID = Compile(shaderSources);
		m_Name = name;
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_RendererID);
	}

	void OpenGLShader::Bind() const
	{
		glUseProgram(m_RendererID);
	}

	void OpenGLShader::Unbind() const
	{
		glUseProgram(0);
	}

	void OpenGLShader::UploadUniformMat4(cstring name, glm::mat4 const & matrix)
	{
		auto location = glGetUniformLocation(m_RendererID, name);
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void OpenGLShader::UploadUniformInt32(cstring name, int32 value)
	{
		auto location = glGetUniformLocation(m_RendererID, name);
		glUniform1i(location, value);
	}
}
