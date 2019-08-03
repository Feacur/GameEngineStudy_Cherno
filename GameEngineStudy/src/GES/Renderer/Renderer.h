#pragma once
#include "GES/Core.h"

namespace GES
{
	class RendererCommand;
	class VertexArray;

	class Renderer
	{
	public:
		static void SetClearColor();
		static void Clear();

	public:
		static void BeginScene();
		static void Submit(std::shared_ptr<VertexArray> const & vertexArray);
		static void EndScene();

	private:
		static RendererCommand * s_RendererCommand;
	};
}
