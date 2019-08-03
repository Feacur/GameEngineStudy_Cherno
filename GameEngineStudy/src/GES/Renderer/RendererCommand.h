#pragma once
#include "GES/Core.h"

namespace GES
{
	class VertexArray;

	class RendererCommand
	{
	public:
		virtual ~RendererCommand() = default;

	public:
		static RendererCommand * Create();

	public:
		virtual void SetClearColor() const = 0;
		virtual void Clear() const = 0;
		virtual void DrawIndexed(std::shared_ptr<VertexArray> const & vertexArray) const = 0;
	};
}
