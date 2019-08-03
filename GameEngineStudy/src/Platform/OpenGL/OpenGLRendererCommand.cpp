#include "ges_pch.h"
#include "OpenGLRendererCommand.h"

#include "GES/Renderer/Buffer.h"
#include "GES/Renderer/VertexArray.h"

#include <glad/glad.h>

namespace GES
{
	void OpenGLRendererCommand::SetClearColor() const
	{
		glClearColor(0.1f, 0.1f, 0.1f, 1);
	}

	void OpenGLRendererCommand::Clear() const
	{
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void OpenGLRendererCommand::DrawIndexed(std::shared_ptr<VertexArray> const & vertexArray) const
	{
		auto & indexBuffer = vertexArray->GetIndexBuffer();
		glDrawElements(GL_TRIANGLES, indexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);
	}
}