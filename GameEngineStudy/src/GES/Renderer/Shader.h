#pragma once
#include "GES/Core.h"

#include <glm/glm.hpp>
#include <string>

namespace GES
{
	class Shader
	{
	public:
		Shader(const char* vertexSource, const char* fragmentSource);
		~Shader();

	public:
		void Bind() const;
		void Unbind() const;

		void UploadUniformMat4(std::string const & name, glm::mat4 const & matrix);

	private:
		uint32 m_RendererID;
	};
}
