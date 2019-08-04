#pragma once
#include "GES/Core.h"

#include <memory> // std::shared_ptr

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

		virtual void AddVertexBuffer(std::shared_ptr<VertexBuffer> const & vertexBuffer) = 0;
		virtual void SetIndexBuffer(std::shared_ptr<IndexBuffer> const & indexBuffer) = 0;
		
		virtual std::vector<std::shared_ptr<VertexBuffer>> const & GetVertexBuffers() const = 0;
		virtual std::shared_ptr<IndexBuffer> const & GetIndexBuffer() const = 0;
	};
}
