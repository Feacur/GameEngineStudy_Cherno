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

		void AddVertexBuffer(Ref<VertexBuffer> const & vertexBuffer) override;
		void SetIndexBuffer(Ref<IndexBuffer> const & indexBuffer) override;

		std::vector<Ref<VertexBuffer>> const & GetVertexBuffers() const { return m_VertexBuffers; }
		Ref<IndexBuffer> const & GetIndexBuffer() const { return m_IndexBuffer; }

	private:
		uint32 m_RendererID;
		std::vector<Ref<VertexBuffer>> m_VertexBuffers;
		Ref<IndexBuffer> m_IndexBuffer;
	};
}