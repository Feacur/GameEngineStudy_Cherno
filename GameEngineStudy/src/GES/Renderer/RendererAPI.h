#pragma once
#include "GES/Core/Code.h"

namespace GES
{
	class VertexArray;

	class RendererAPI
	{
	public:
		virtual ~RendererAPI() = default;

	public:
		static Scope<RendererAPI> Create();

	public:
		virtual void SetClearColor() const = 0;
		virtual void Clear() const = 0;
		virtual void Init() const = 0;
		virtual void SetViewport(uint32 x, uint32 y, uint32 width, uint32 height) = 0;

		virtual void DrawIndexed(Ref<VertexArray> const & vertexArray) const = 0;
	};
}
