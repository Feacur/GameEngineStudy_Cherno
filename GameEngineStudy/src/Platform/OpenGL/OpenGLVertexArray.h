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

		void AddVertexBuffer(GES::Ref<VertexBuffer> const & vertexBuffer) override;
		void SetIndexBuffer(GES::Ref<IndexBuffer> const & indexBuffer) override;

		std::vector<GES::Ref<VertexBuffer>> const & GetVertexBuffers() const { return m_VertexBuffers; }
		GES::Ref<IndexBuffer> const & GetIndexBuffer() const { return m_IndexBuffer; }

	private:
		uint32 m_RendererID;
		std::vector<GES::Ref<VertexBuffer>> m_VertexBuffers;
		GES::Ref<IndexBuffer> m_IndexBuffer;
	};
}