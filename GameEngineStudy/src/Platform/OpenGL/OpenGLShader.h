#pragma once
#include "GES/Renderer/Shader.h"

namespace GES
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(cstring vertexSource, cstring fragmentSource);
		~OpenGLShader() override;

	public:
		void Bind() const override;
		void Unbind() const override;

		void UploadUniformMat4(cstring name, glm::mat4 const & matrix) override;

	private:
		uint32 m_RendererID;
	};
}
