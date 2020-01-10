#pragma once
#include "GES/Core/Code.h"

#if !defined(GES_BYPASS_VENDOR_HEADERS)
	#include <glm/glm.hpp>

	#include <string>
	#include <unordered_map>
#endif

namespace GES
{
	class Shader
	{
	public:
		virtual ~Shader() = default;

	public:
		static Ref<Shader> Shader::CreatePath(cstring path, cstring name = 0);
		static Ref<Shader> Shader::CreateSource(cstring source, cstring name = 0);

	public:
		virtual std::string const & GetName() const = 0;
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void UploadUniformMat4(cstring name, glm::mat4 const & value) = 0;

		virtual void UploadUniformInt(cstring name, int32 value) = 0;

		virtual void UploadUniformFloat1(cstring name, float value) = 0;
		virtual void UploadUniformFloat2(cstring name, glm::vec2 const & value) = 0;
		virtual void UploadUniformFloat3(cstring name, glm::vec3 const & value) = 0;
		virtual void UploadUniformFloat4(cstring name, glm::vec4 const & value) = 0;
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
