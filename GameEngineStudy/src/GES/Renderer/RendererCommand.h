#pragma once
#include "GES/Core/Code.h"

namespace GES
{
	class VertexArray;

	class RendererCommand
	{
	public:
		static void Init();

		static void SetClearColor();
		static void Clear();
		static void SetViewport(uint32 x, uint32 y, uint32 width, uint32 height);

		static void DrawIndexed(Ref<VertexArray> const & vertexArray);
	};
}
