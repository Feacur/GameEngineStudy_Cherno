#pragma once
#include "GES/Renderer/RendererCommand.h"

namespace GES
{
	class OpenGLRendererCommand : public RendererCommand
	{
	public:
		OpenGLRendererCommand() = default;
		~OpenGLRendererCommand() override = default;

	public:
		void SetClearColor() const override;
		void Clear() const override;

		void DrawIndexed(std::shared_ptr<VertexArray> const & vertexArray) const override;
	};
}