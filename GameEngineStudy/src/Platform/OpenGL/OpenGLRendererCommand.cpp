#include "ges_pch.h"
#include "OpenGLRendererCommand.h"

#include "GES/Log.h"

#include "GES/Renderer/Buffer.h"
#include "GES/Renderer/VertexArray.h"

#include <glad/glad.h>

namespace GES
{
	void OpenGLMessageCallback(
		unsigned source,
		unsigned type,
		unsigned id,
		unsigned severity,
		int length,
		const char* message,
		const void* userParam)
	{
		switch (severity)
		{
			case GL_DEBUG_SEVERITY_HIGH:         GES_CORE_CRITICAL(message); return;
			case GL_DEBUG_SEVERITY_MEDIUM:       GES_CORE_ERROR(message); return;
			case GL_DEBUG_SEVERITY_LOW:          GES_CORE_WARN(message); return;
			case GL_DEBUG_SEVERITY_NOTIFICATION: GES_CORE_TRACE(message); return;
		}
		GES_CORE_ASSERT(false, "Unknown severity level!");
	}

	void OpenGLRendererCommand::SetClearColor() const
	{
		glClearColor(0.1f, 0.1f, 0.1f, 1);
	}

	void OpenGLRendererCommand::Clear() const
	{
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void OpenGLRendererCommand::Init() const
	{
		#if !defined(GES_SHIPPING)
			glEnable(GL_DEBUG_OUTPUT);
			glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
			glDebugMessageCallback(OpenGLMessageCallback, nullptr);
			glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, NULL, GL_FALSE);
		#endif
		
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void OpenGLRendererCommand::DrawIndexed(Ref<VertexArray> const & vertexArray) const
	{
		auto & indexBuffer = vertexArray->GetIndexBuffer();
		glDrawElements(GL_TRIANGLES, indexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);
	}
}