#pragma once
#include "GES/Renderer/Buffer.h"

namespace GES
{
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(float * vertices, u32 size);
		~OpenGLVertexBuffer() override;

	public:
		void Bind() const override;
		void Unbind() const override;

		void SetLayout(BufferLayout const & layout) override { m_Layout = layout; }
		BufferLayout const & GetLayout() const override { return m_Layout; }

	private:
		u32 m_RendererID;
		BufferLayout m_Layout;
	};
	
	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(u32 * indices, u32 count);
		~OpenGLIndexBuffer() override;

	public:
		void Bind() const override;
		void Unbind() const override;

		u32 GetCount() const override { return m_Count; }

	private:
		u32 m_RendererID;
		u32 m_Count;
	};
}