#pragma once
#include "GES/Core.h"

namespace GES
{
	class VertexBuffer;
	class IndexBuffer;

	class VertexArray
	{
	public:
		virtual ~VertexArray() = default;

	public:
		static VertexArray * Create();

	public:
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void AddVertexBuffer(GES::Ref<VertexBuffer> const & vertexBuffer) = 0;
		virtual void SetIndexBuffer(GES::Ref<IndexBuffer> const & indexBuffer) = 0;
		
		virtual std::vector<GES::Ref<VertexBuffer>> const & GetVertexBuffers() const = 0;
		virtual GES::Ref<IndexBuffer> const & GetIndexBuffer() const = 0;
	};
}
