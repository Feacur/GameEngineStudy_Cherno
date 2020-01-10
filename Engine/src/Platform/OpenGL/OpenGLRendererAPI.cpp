#include "ges_pch.h"
#include "OpenGLRendererAPI.h"

#include "GES/Debug/Log.h"
#include "GES/Debug/Instrumentor.h"
#include "GES/Debug/Code.h"

#include "GES/Renderer/Buffer.h"
#include "GES/Renderer/VertexArray.h"

#include <glad/glad.h>

namespace GES
{
	static void OpenGLMessageCallback(
		unsigned source,
		unsigned type,
		unsigned id,
		unsigned severity,
		int length,
		const char* message,
		const void* userParam)
	{
		GES_PROFILE_FUNCTION();
		switch (severity)
		{
			case GL_DEBUG_SEVERITY_HIGH:         GES_CORE_CRITICAL(message); return;
			case GL_DEBUG_SEVERITY_MEDIUM:       GES_CORE_ERROR(message); return;
			case GL_DEBUG_SEVERITY_LOW:          GES_CORE_WARN(message); return;
			case GL_DEBUG_SEVERITY_NOTIFICATION: GES_CORE_TRACE(message); return;
		}
		GES_CORE_ASSERT(false, "Unknown severity level!");
	}

	void OpenGLRendererAPI::Init() const
	{
		GES_PROFILE_FUNCTION();
		#if defined(GES_LOGGER_ENABLED)
			glEnable(GL_DEBUG_OUTPUT);
			glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
			glDebugMessageCallback(OpenGLMessageCallback, nullptr);
			glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, NULL, GL_FALSE);
		#endif

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glEnable(GL_DEPTH_TEST);
		// glDepthFunc(GL_LESS);
		// glDepthRangef(0.0f, 1.0f);
		// glClearDepth(1.0f);

		// glCullFace(GL_BACK);
	}

	void OpenGLRendererAPI::Shutdown() const
	{
		GES_PROFILE_FUNCTION();
	}

	void OpenGLRendererAPI::SetClearColor(glm::vec4 const & color) const
	{
		GES_PROFILE_FUNCTION();
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void OpenGLRendererAPI::Clear() const
	{
		GES_PROFILE_FUNCTION();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRendererAPI::SetViewport(uint32 x, uint32 y, uint32 width, uint32 height)
	{
		GES_PROFILE_FUNCTION();
		glViewport(x, y, width, height);
	}

	void OpenGLRendererAPI::DrawIndexed(Ref<VertexArray> const & vertexArray) const
	{
		GES_PROFILE_FUNCTION();
		auto & indexBuffer = vertexArray->GetIndexBuffer();
		glDrawElements(GL_TRIANGLES, indexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);
	}

	void OpenGLRendererAPI::DrawTriangle() const
	{
		GES_PROFILE_FUNCTION();
		// send to a vertex shader indices [0, 1, 2]
		glDrawArrays(GL_TRIANGLES, 0, 3);
		// https://rauwendaal.net/2014/06/14/rendering-a-screen-covering-triangle-in-opengl/
		// https://twitter.com/nice_byte/status/1093355080235999232
	}
}