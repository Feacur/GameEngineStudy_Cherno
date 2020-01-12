#include "ges_pch.h"
#include "Renderer.h"

#include "Orthographic2dCamera.h"

#include "RendererCommand.h"
#include "Shader.h"
#include "Texture.h"
#include "VertexArray.h"

#include "GES/Debug/Instrumentor.h"
#include "GES/Debug/Code.h"

namespace GES
{
	struct Data
	{
		glm::mat4 ViewProjectionMatrix;
	};
	static Data * s_Data;
	
	void Renderer::Init()
	{
		GES_PROFILE_FUNCTION();
		s_Data = new Data();
	}
	
	void Renderer::Shutdown()
	{
		GES_PROFILE_FUNCTION();
		delete s_Data;
	}

	void Renderer::BeginScene(Orthographic2dCamera const & camera)
	{
		GES_PROFILE_FUNCTION();
		s_Data->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}

	void Renderer::EndScene()
	{
		GES_PROFILE_FUNCTION();
	}

	void Renderer::Submit(Ref<Shader> const & shader, Ref<VertexArray> const & vertexArray, glm::mat4 const & transform)
	{
		GES_PROFILE_FUNCTION();
		shader->Bind();
		shader->UploadUniformMat4("u_ViewProjection", s_Data->ViewProjectionMatrix);
		shader->UploadUniformMat4("u_Transform", transform);

		vertexArray->Bind();
		RendererCommand::DrawIndexed(vertexArray);
	}

	void Renderer::Submit(Ref<Shader> const & shader, Ref<VertexArray> const & vertexArray, glm::mat4 const & transform, Ref<Texture2D> const & texture)
	{
		GES_PROFILE_FUNCTION();
		texture->Bind(0u);

		shader->Bind();
		shader->UploadUniformMat4("u_ViewProjectionMatrix", s_Data->ViewProjectionMatrix);
		shader->UploadUniformMat4("u_Transform", transform);
		shader->UploadUniformInt("u_Texture", (s32)texture->GetSlot());

		vertexArray->Bind();
		RendererCommand::DrawIndexed(vertexArray);
	}
}
