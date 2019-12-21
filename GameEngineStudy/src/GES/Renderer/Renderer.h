#pragma once
#include "GES/Core.h"

#if !defined(GES_BYPASS_VENDOR_HEADERS)
	#include <glm/glm.hpp>
#endif

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
		static void OnWindowResize(uint32 width, uint32 height);

	public:
		static void BeginScene(Orthographic2dCamera const & camera);
		static void Submit(Ref<Shader> const & shader, Ref<VertexArray> const & vertexArray, glm::mat4 const & transform);
		static void Submit(Ref<Shader> const & shader, Ref<VertexArray> const & vertexArray, glm::mat4 const & transform, Ref<Texture> const & texture);
		static void EndScene();

	private:
		static Ref<RendererCommand> s_RendererCommand;

	private:
		struct Data
		{
			glm::mat4 ViewProjectionMatrix;
		};

		static Scope<Data> s_Data;
	};
}
