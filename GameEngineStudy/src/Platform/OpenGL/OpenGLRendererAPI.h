#pragma once
#include "GES/Renderer/RendererAPI.h"

namespace GES
{
	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		OpenGLRendererAPI() = default;
		~OpenGLRendererAPI() override = default;

	public:
		void Init() const override;
		void Shutdown() const override;

		void SetClearColor(glm::vec4 const & color) const override;
		void Clear() const override;
		void SetViewport(uint32 x, uint32 y, uint32 width, uint32 height) override;

		void DrawIndexed(Ref<VertexArray> const & vertexArray) const override;
		void DrawTriangle() const override;
	};
}