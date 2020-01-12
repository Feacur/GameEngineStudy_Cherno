#include "ges_pch.h"
#include "RendererCommand.h"

#include "GES/Debug/Instrumentor.h"
#include "GES/Debug/Code.h"

#include "RendererAPI.h"

#include "GES/Debug/Instrumentor.h"
#include "GES/Debug/Code.h"

namespace GES
{
	static Scope<RendererAPI> s_RendererAPI = nullptr;

	void RendererCommand::Init()
	{
		GES_PROFILE_FUNCTION();
		s_RendererAPI = RendererAPI::Create();
		s_RendererAPI->Init();
	}

	void RendererCommand::Shutdown()
	{
		GES_PROFILE_FUNCTION();
		s_RendererAPI->Shutdown();
	}

	void RendererCommand::SetClearColor(glm::vec4 const & color)
	{
		GES_PROFILE_FUNCTION();
		s_RendererAPI->SetClearColor(color);
	}

	void RendererCommand::Clear()
	{
		GES_PROFILE_FUNCTION();
		s_RendererAPI->Clear();
	}

	void RendererCommand::SetViewport(u32 x, u32 y, u32 width, u32 height)
	{
		GES_PROFILE_FUNCTION();
		s_RendererAPI->SetViewport(x, y, width, height);
	}

	void RendererCommand::DrawIndexed(Ref<VertexArray> const & vertexArray)
	{
		GES_PROFILE_FUNCTION();
		s_RendererAPI->DrawIndexed(vertexArray);
	}

	void RendererCommand::DrawTriangle()
	{
		GES_PROFILE_FUNCTION();
		s_RendererAPI->DrawTriangle();
	}
}
