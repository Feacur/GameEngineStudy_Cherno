#pragma once
#include "GES/Core/Code.h"

#if !defined(GES_BYPASS_VENDOR_HEADERS)
	#include <glm/glm.hpp>
#endif

namespace GES
{
	class VertexArray;

	class RendererCommand
	{
	public:
		static void Init();
		static void Shutdown();

		static void SetClearColor(glm::vec4 const & color);
		static void Clear();
		static void SetViewport(u32 x, u32 y, u32 width, u32 height);

		static void DrawIndexed(Ref<VertexArray> const & vertexArray);
		static void DrawTriangle();
	};
}
