#pragma once

namespace GES
{
	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() = default;

	public:
		static VertexBuffer * Create(float * vertices, uint32 size);

	public:
		virtual void Bind() = 0;
		virtual void Unbind() = 0;
	};
	
	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() = default;

	public:
		static IndexBuffer * Create(uint32 * indices, uint32 size);

	public:
		virtual void Bind() = 0;
		virtual void Unbind() = 0;
		
		virtual uint32 GetCount() const = 0;
	};
}