#pragma once
#include "GES/Core/Code.h"

namespace GES
{
	class VertexBuffer;
	class IndexBuffer;

	class VertexArray
	{
	public:
		virtual ~VertexArray() = default;

	public:
		static Ref<VertexArray> Create();

	public:
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void AddVertexBuffer(Ref<VertexBuffer> const & vertexBuffer) = 0;
		virtual void SetIndexBuffer(Ref<IndexBuffer> const & indexBuffer) = 0;
		
		virtual std::vector<Ref<VertexBuffer>> const & GetVertexBuffers() const = 0;
		virtual Ref<IndexBuffer> const & GetIndexBuffer() const = 0;
	};
}
