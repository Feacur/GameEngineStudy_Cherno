#pragma once
#include "GES/Core/Code.h"

#if !defined(GES_BYPASS_VENDOR_HEADERS)
	#include <glm/glm.hpp>
#endif

namespace GES
{
	class Orthographic2dCamera;
	class Shader;
	class Texture;
	class VertexArray;

	class Renderer
	{
	public:
		static void Init();
		static void Shutdown();

		static void SetClearColor(glm::vec4 const & color);
		static void Clear();
		static void OnWindowResize(uint32 width, uint32 height);

	public:
		static void BeginScene(Orthographic2dCamera const & camera);
		static void Submit(Ref<Shader> const & shader, Ref<VertexArray> const & vertexArray, glm::mat4 const & transform);
		static void Submit(Ref<Shader> const & shader, Ref<VertexArray> const & vertexArray, glm::mat4 const & transform, Ref<Texture> const & texture);
		static void EndScene();
	};
}
