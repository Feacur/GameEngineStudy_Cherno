#include "ges_pch.h"
#include "OpenGLShader.h"

#include "GES/Debug/Log.h"
#include "GES/Debug/Instrumentor.h"
#include "GES/Debug/Code.h"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

typedef GLchar const * glstring;

namespace GES
{
	static GLenum ShaderTypeFromString(std::string const & type)
	{
		GES_PROFILE_FUNCTION();
		if (type == "vertex") {
			return GL_VERTEX_SHADER;
		}

		if (type == "fragment" || type == "pixel") {
			return GL_FRAGMENT_SHADER;
		}

		GES_CORE_ASSERT(false, "Unknown shader type");
		return 0;
	}

	static std::unordered_map<GLenum, std::string> PreProcess(std::string const & source)
	{
		GES_PROFILE_FUNCTION();
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

	static GLuint Compile(const std::unordered_map<GLenum, std::string>& shaderSources)
	{
		GES_PROFILE_FUNCTION();
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
		GES_PROFILE_FUNCTION();
		auto shaderSources = PreProcess(source);
		m_RendererID = Compile(shaderSources);
		m_Name = name;
	}

	OpenGLShader::~OpenGLShader()
	{
		GES_PROFILE_FUNCTION();
		glDeleteProgram(m_RendererID);
	}

	void OpenGLShader::Bind() const
	{
		GES_PROFILE_FUNCTION();
		glUseProgram(m_RendererID);
	}

	void OpenGLShader::Unbind() const
	{
		GES_PROFILE_FUNCTION();
		glUseProgram(0);
	}

	void OpenGLShader::UploadUniformMat4(cstring name, glm::mat4 const & value)
	{
		GES_PROFILE_FUNCTION();
		auto location = glGetUniformLocation(m_RendererID, name);
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
	}

	void OpenGLShader::UploadUniformInt(cstring name, int32 value)
	{
		GES_PROFILE_FUNCTION();
		auto location = glGetUniformLocation(m_RendererID, name);
		glUniform1i(location, value);
	}

	void OpenGLShader::UploadUniformFloat1(cstring name, float value)
	{
		GES_PROFILE_FUNCTION();
		auto location = glGetUniformLocation(m_RendererID, name);
		glUniform1f(location, value);
	}

	void OpenGLShader::UploadUniformFloat2(cstring name, glm::vec2 const & value)
	{
		GES_PROFILE_FUNCTION();
		auto location = glGetUniformLocation(m_RendererID, name);
		glUniform2f(location, value.x, value.y);
	}

	void OpenGLShader::UploadUniformFloat3(cstring name, glm::vec3 const & value)
	{
		GES_PROFILE_FUNCTION();
		auto location = glGetUniformLocation(m_RendererID, name);
		glUniform3f(location, value.x, value.y, value.z);
	}

	void OpenGLShader::UploadUniformFloat4(cstring name, glm::vec4 const & value)
	{
		GES_PROFILE_FUNCTION();
		auto location = glGetUniformLocation(m_RendererID, name);
		glUniform4f(location, value.x, value.y, value.z, value.w);
	}
}