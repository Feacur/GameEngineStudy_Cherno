#pragma once
#include "GES/Renderer/Shader.h"

namespace GES
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(cstring source, cstring name);
		~OpenGLShader() override;

	public:
		std::string const & GetName() const override { return m_Name; }
		void Bind() const override;
		void Unbind() const override;

		void UploadUniformMat4(cstring name, glm::mat4 const & value) override;
		
		void UploadUniformInt(cstring name, s32 value) override;

		void UploadUniformFloat1(cstring name, float value) override;
		void UploadUniformFloat2(cstring name, glm::vec2 const & value) override;
		void UploadUniformFloat3(cstring name, glm::vec3 const & value) override;
		void UploadUniformFloat4(cstring name, glm::vec4 const & value) override;

	private:
		u32 m_RendererID;
		std::string m_Name;
	};
}
