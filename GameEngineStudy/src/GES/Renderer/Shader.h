#pragma once

#include "GES/Core.h"

#include <glm/glm.hpp>

namespace GES
{
	class Shader
	{
	public:
		virtual ~Shader() = default;

	public:
		static Shader * Shader::Create(cstring vertexSource, cstring fragmentSource);

	public:
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void UploadUniformMat4(cstring name, glm::mat4 const & matrix) = 0;
		virtual void UploadUniformInt32(cstring name, int32 value) = 0;
	};
}
