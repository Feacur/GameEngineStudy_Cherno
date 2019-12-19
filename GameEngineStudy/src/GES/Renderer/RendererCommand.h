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
		static Ref<RendererCommand> Create();

	public:
		virtual void SetClearColor() const = 0;
		virtual void Clear() const = 0;
		virtual void Init() const = 0;
		virtual void DrawIndexed(Ref<VertexArray> const & vertexArray) const = 0;
	};
}
