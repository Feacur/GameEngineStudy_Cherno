#pragma once
#include "GES/Core/Code.h"

#if !defined(GES_BYPASS_VENDOR_HEADERS)
	#include <glm/glm.hpp>
#endif

namespace GES
{
	class VertexArray;

	class RendererAPI
	{
	public:
		virtual ~RendererAPI() = default;

	public:
		static Scope<RendererAPI> Create();

	public:
		virtual void Init() const = 0;
		virtual void Shutdown() const = 0;

		virtual void SetClearColor(glm::vec4 const & color) const = 0;
		virtual void Clear() const = 0;
		virtual void SetViewport(uint32 x, uint32 y, uint32 width, uint32 height) = 0;

		virtual void DrawIndexed(Ref<VertexArray> const & vertexArray) const = 0;
	};
}
