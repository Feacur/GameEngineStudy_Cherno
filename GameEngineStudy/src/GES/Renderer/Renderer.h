#pragma once
#include "GES/Core.h"

#include <glm/glm.hpp>

#include <memory> // std::shared_ptr

namespace GES
{
	class Orthographic2dCamera;
	class RendererCommand;
	class Shader;
	class VertexArray;

	class Renderer
	{
	public:
		static void SetClearColor();
		static void Clear();

	public:
		static void BeginScene(Orthographic2dCamera const & camera);
		static void Submit(std::shared_ptr<Shader> const & shader, std::shared_ptr<VertexArray> const & vertexArray);
		static void EndScene();

	private:
		static RendererCommand * s_RendererCommand;

	private:
		struct Data
		{
			glm::mat4 ViewProjectionMatrix;
		};

		static Data * s_Data;
	};
}
