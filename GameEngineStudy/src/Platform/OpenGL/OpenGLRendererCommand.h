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
		void Init() const override;

		void DrawIndexed(Ref<VertexArray> const & vertexArray) const override;
	};
}