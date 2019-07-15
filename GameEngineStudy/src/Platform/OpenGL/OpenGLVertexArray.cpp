#include "ges_pch.h"
#include "OpenGLVertexArray.h"

#include "GES/Renderer/Buffer.h"

#include <glad/glad.h>

namespace GES
{
	static GLenum ShaderDataTypeOpenGLBaseType(ShaderDataType type)
	{
		switch(type)
		{
			case ShaderDataType::Float1: return GL_FLOAT;
			case ShaderDataType::Float2: return GL_FLOAT;
			case ShaderDataType::Float3: return GL_FLOAT;
			case ShaderDataType::Float4: return GL_FLOAT;
			case ShaderDataType::Mat3:   return GL_FLOAT;
			case ShaderDataType::Mat4:   return GL_FLOAT;
			case ShaderDataType::Int1:   return GL_INT;
			case ShaderDataType::Int2:   return GL_INT;
			case ShaderDataType::Int3:   return GL_INT;
			case ShaderDataType::Int4:   return GL_INT;
			case ShaderDataType::Bool:   return GL_BOOL;
		}
		GES_CORE_ASSERT(false, "unsupported ShaderDataType '{0}'", (int32)type);
		return 0;
	}
	
	OpenGLVertexArray::OpenGLVertexArray()
	{
		glGenVertexArrays(1, &m_RendererID);
		glBindVertexArray(m_RendererID);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
	}

	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(m_RendererID);
	}

	void OpenGLVertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}
	
	void OpenGLVertexArray::AddVertexBuffer(std::shared_ptr<VertexBuffer> const & vertexBuffer)
	{
		glBindVertexArray(m_RendererID);
		vertexBuffer->Bind();
		m_VertexBuffers.push_back(vertexBuffer);
		
		uint32 vertexAttribIndex = 0;
		auto const & bufferLayout = vertexBuffer->GetLayout();
		for (auto const & element : bufferLayout)
		{
			glEnableVertexAttribArray(vertexAttribIndex);
			glVertexAttribPointer(
				vertexAttribIndex,
				element.GetComponentCount(),
				ShaderDataTypeOpenGLBaseType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				bufferLayout.GetStride(),
				(void const *)(uintptr_t)element.Offset
			);
			vertexAttribIndex++;
		}
	}

	void OpenGLVertexArray::SetIndexBuffer(std::shared_ptr<IndexBuffer> const & indexBuffer)
	{
		glBindVertexArray(m_RendererID);
		indexBuffer->Bind();
		m_IndexBuffer = indexBuffer;
	}
}