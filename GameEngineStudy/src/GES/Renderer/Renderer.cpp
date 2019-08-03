#include "ges_pch.h"
#include "Renderer.h"

#include "RendererCommand.h"
#include "VertexArray.h"

namespace GES
{
	RendererCommand * Renderer::s_RendererCommand = RendererCommand::Create();
	
	void Renderer::SetClearColor()
	{
		s_RendererCommand->SetClearColor();
	}

	void Renderer::Clear()
	{
		s_RendererCommand->Clear();
	}

	void Renderer::BeginScene()
	{
	}

	void Renderer::Submit(std::shared_ptr<VertexArray> const & vertexArray)
	{
		vertexArray->Bind();
		s_RendererCommand->DrawIndexed(vertexArray);
	}

	void Renderer::EndScene()
	{
	}
}
