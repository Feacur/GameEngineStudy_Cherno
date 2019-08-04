#pragma once

#include "GES/Renderer/VertexArray.h"

namespace GES
{
	class OpenGLVertexArray : public VertexArray
	{
	public:
		OpenGLVertexArray();
		~OpenGLVertexArray() override;

	public:
		void Bind() const override;
		void Unbind() const override;

		void AddVertexBuffer(std::shared_ptr<VertexBuffer> const & vertexBuffer) override;
		void SetIndexBuffer(std::shared_ptr<IndexBuffer> const & indexBuffer) override;

		std::vector<std::shared_ptr<VertexBuffer>> const & GetVertexBuffers() const { return m_VertexBuffers; }
		std::shared_ptr<IndexBuffer> const & GetIndexBuffer() const { return m_IndexBuffer; }

	private:
		uint32 m_RendererID;
		std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffers;
		std::shared_ptr<IndexBuffer> m_IndexBuffer;
	};
}