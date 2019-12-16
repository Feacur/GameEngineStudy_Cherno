#pragma once
#include "GES/Core.h"

#include <glm/glm.hpp>

namespace GES
{
	class Orthographic2dCamera;
	class RendererCommand;
	class Shader;
	class Texture;
	class VertexArray;

	class Renderer
	{
	public:
		static void SetClearColor();
		static void Clear();

		static void Init();

	public:
		static void BeginScene(Orthographic2dCamera const & camera);
		static void Submit(GES::Ref<Shader> const & shader, GES::Ref<VertexArray> const & vertexArray, glm::mat4 const & transform);
		static void Submit(GES::Ref<Shader> const & shader, GES::Ref<VertexArray> const & vertexArray, glm::mat4 const & transform, GES::Ref<Texture> const & texture);
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
