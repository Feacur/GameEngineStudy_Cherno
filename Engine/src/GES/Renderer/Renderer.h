#pragma once
#include "GES/Core/Code.h"

#if !defined(GES_BYPASS_VENDOR_HEADERS)
	#include <glm/glm.hpp>
#endif

namespace GES
{
	class Orthographic2dCamera;
	class Shader;
	class Texture2D;
	class VertexArray;

	class Renderer
	{
	public:
		static void Init();
		static void Shutdown();

	public:
		static void BeginScene(Orthographic2dCamera const & camera);
		static void EndScene();

		static void Submit(Ref<Shader> const & shader, Ref<VertexArray> const & vertexArray, glm::mat4 const & transform);
		static void Submit(Ref<Shader> const & shader, Ref<VertexArray> const & vertexArray, glm::mat4 const & transform, Ref<Texture2D> const & texture);
	};
}
