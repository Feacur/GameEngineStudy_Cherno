#include "ges_pch.h"
#include "RendererCommand.h"

#include "RendererAPI.h"

namespace GES
{
	static Scope<RendererAPI> s_RendererAPI = RendererAPI::Create();

	void RendererCommand::SetClearColor(glm::vec4 const & color)
	{
		s_RendererAPI->SetClearColor(color);
	}

	void RendererCommand::Clear()
	{
		s_RendererAPI->Clear();
	}

	void RendererCommand::Init()
	{
		s_RendererAPI->Init();
	}

	void RendererCommand::SetViewport(uint32 x, uint32 y, uint32 width, uint32 height)
	{
		s_RendererAPI->SetViewport(x, y, width, height);
	}

	void RendererCommand::DrawIndexed(Ref<VertexArray> const & vertexArray)
	{
		s_RendererAPI->DrawIndexed(vertexArray);
	}
}
