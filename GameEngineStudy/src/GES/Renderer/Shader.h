#pragma once

#include "GES/Core.h"

#include <glm/glm.hpp>

#include <string>
#include <unordered_map>

namespace GES
{
	class Shader
	{
	public:
		virtual ~Shader() = default;

	public:
		static Shader * Shader::CreatePath(cstring path, cstring name = 0);
		static Shader * Shader::CreateSource(cstring source, cstring name = 0);

	public:
		virtual std::string const & GetName() const = 0;
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void UploadUniformMat4(cstring name, glm::mat4 const & matrix) = 0;
		virtual void UploadUniformInt32(cstring name, int32 value) = 0;
	};
	
	class ShaderLibrary
	{
	public:
		void Add(Ref<Shader> const & shader);
		Ref<Shader> Get(cstring name);

	private:
		std::unordered_map<std::string, Ref<Shader>> m_Shaders;
	};
}
