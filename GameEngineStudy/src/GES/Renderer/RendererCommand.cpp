#include "ges_pch.h"
#include "RendererCommand.h"

#include "RendererAPI.h"

namespace GES
{
	static Scope<RendererAPI> s_RendererAPI = RendererAPI::Create();

	void RendererCommand::SetClearColor()
	{
		s_RendererAPI->SetClearColor();
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
