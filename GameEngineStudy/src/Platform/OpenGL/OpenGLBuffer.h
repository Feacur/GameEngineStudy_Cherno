#pragma once
#include "GES/Renderer/Buffer.h"

namespace GES
{
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(float * vertices, uint32 size);
		~OpenGLVertexBuffer() override;

	public:
		void Bind() override;
		void Unbind() override;

	private:
		uint32 m_RendererID;
	};
	
	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(uint32 * indices, uint32 count);
		~OpenGLIndexBuffer() override;

	public:
		void Bind() override;
		void Unbind() override;

		uint32 GetCount() const override { return m_Count; }

	private:
		uint32 m_RendererID;
		uint32 m_Count;
	};
}