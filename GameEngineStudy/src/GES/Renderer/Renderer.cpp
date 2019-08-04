#include "ges_pch.h"
#include "Renderer.h"

#include "GES/Renderer/Orthographic2dCamera.h"

#include "RendererCommand.h"
#include "Shader.h"
#include "VertexArray.h"

namespace GES
{
	Renderer::Data * Renderer::s_Data = new Data();
	RendererCommand * Renderer::s_RendererCommand = RendererCommand::Create();
	
	void Renderer::SetClearColor()
	{
		s_RendererCommand->SetClearColor();
	}

	void Renderer::Clear()
	{
		s_RendererCommand->Clear();
	}

	void Renderer::BeginScene(Orthographic2dCamera const & camera)
	{
		s_Data->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}

	void Renderer::Submit(std::shared_ptr<Shader> const & shader, std::shared_ptr<VertexArray> const & vertexArray)
	{
		shader->Bind();
		shader->UploadUniformMat4("u_ViewProjectionMatrix", s_Data->ViewProjectionMatrix);

		vertexArray->Bind();
		s_RendererCommand->DrawIndexed(vertexArray);
	}

	void Renderer::EndScene()
	{
	}
}
