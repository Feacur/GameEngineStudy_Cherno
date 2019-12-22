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

	class Renderer2D
	{
	public:
		static void Init();
		static void Shutdown();

	public:
		static void BeginScene(Orthographic2dCamera const & camera);
		static void EndScene();

		static void DrawQuad(glm::vec2 const & position, glm::vec2 const & size, glm::vec4 const & color);
		static void DrawQuad(glm::vec3 const & position, glm::vec2 const & size, glm::vec4 const & color);
	};
}
