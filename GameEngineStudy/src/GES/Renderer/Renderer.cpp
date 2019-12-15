#include "ges_pch.h"
#include "Renderer.h"

#include "GES/Renderer/Orthographic2dCamera.h"

#include "RendererCommand.h"
#include "Shader.h"
#include "Texture.h"
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

	void Renderer::Submit(std::shared_ptr<Shader> const & shader, std::shared_ptr<VertexArray> const & vertexArray, glm::mat4 const & transform)
	{
		shader->Bind();
		shader->UploadUniformMat4("u_ViewProjectionMatrix", s_Data->ViewProjectionMatrix);
		shader->UploadUniformMat4("u_Transform", transform);

		vertexArray->Bind();
		s_RendererCommand->DrawIndexed(vertexArray);
	}

	void Renderer::Submit(std::shared_ptr<Shader> const & shader, std::shared_ptr<VertexArray> const & vertexArray, glm::mat4 const & transform, std::shared_ptr<Texture> const & texture)
	{
		shader->Bind();
		shader->UploadUniformMat4("u_ViewProjectionMatrix", s_Data->ViewProjectionMatrix);
		shader->UploadUniformMat4("u_Transform", transform);
		shader->UploadUniformInt32("u_Texture", (int32)texture->GetSlot());

		vertexArray->Bind();
		s_RendererCommand->DrawIndexed(vertexArray);
	}

	void Renderer::EndScene()
	{
	}
}
