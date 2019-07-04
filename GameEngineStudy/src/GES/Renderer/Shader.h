#pragma once
#include "GES/Core.h"

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

	private:
		uint32 m_RendererID;
	};
}
