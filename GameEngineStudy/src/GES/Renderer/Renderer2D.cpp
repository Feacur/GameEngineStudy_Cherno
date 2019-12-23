#include "ges_pch.h"
#include "Renderer2D.h"

#include "Orthographic2dCamera.h"

#include "RendererCommand.h"
#include "Shader.h"
#include "Texture.h"
#include "Buffer.h"
#include "VertexArray.h"

#include <glm/gtc/matrix_transform.hpp>

namespace GES
{
	struct Data
	{
		Ref<VertexArray> QuadVertexArray;
		Ref<Shader> TextureShader;
		Ref<Texture2D> WhiteTexture;
	};
	static Data * s_Data;
	static uint32 const s_TextureSlot = 0;

	static Ref<VertexArray> CreateQuadVertexArray()
	{
		auto vertexArray = VertexArray::Create();

		float vertices[] = {
			/*position*/ -0.5f, -0.5f, 0.0f, /*UV*/ 0.0f, 0.0f,
			/*position*/  0.5f, -0.5f, 0.0f, /*UV*/ 1.0f, 0.0f,
			/*position*/  0.5f,  0.5f, 0.0f, /*UV*/ 1.0f, 1.0f,
			/*position*/ -0.5f,  0.5f, 0.0f, /*UV*/ 0.0f, 1.0f,
		};
		auto vertexBuffer = VertexBuffer::Create(vertices, sizeof(vertices));
		vertexBuffer->SetLayout({
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float2, "a_TexCoord" },
		});
		vertexArray->AddVertexBuffer(vertexBuffer);

		uint32 indices[] = {
			0, 1, 2,
			2, 3, 0,
		};
		auto indexBuffer = IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32));
		vertexArray->SetIndexBuffer(indexBuffer);
		
		return vertexArray;
	}
	
	void Renderer2D::Init()
	{
		s_Data = new Data();
		s_Data->QuadVertexArray = CreateQuadVertexArray();
		s_Data->TextureShader = GES::Shader::CreatePath("assets/shaders/texture.glsl");
		
		uint32 whiteTextureData = 0xffffffff;
		s_Data->WhiteTexture = Texture2D::Create(1u, 1u);
		s_Data->WhiteTexture->SetData(&whiteTextureData, sizeof(whiteTextureData));

		s_Data->TextureShader->Bind();
		s_Data->TextureShader->UploadUniformInt("u_Texture", (int32)s_TextureSlot);
	}
	
	void Renderer2D::Shutdown()
	{
		delete s_Data;
	}

	void Renderer2D::BeginScene(Orthographic2dCamera const & camera)
	{
		s_Data->TextureShader->Bind();
		s_Data->TextureShader->UploadUniformMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
		
		s_Data->QuadVertexArray->Bind();
	}

	void Renderer2D::EndScene()
	{
	}
	
	void Renderer2D::DrawQuad(glm::vec2 const & position, glm::vec2 const & size, glm::vec4 const & color)
	{
		DrawQuad({position.x, position.y, 0.0f}, size, color, s_Data->WhiteTexture);
	}

	void Renderer2D::DrawQuad(glm::vec3 const & position, glm::vec2 const & size, glm::vec4 const & color)
	{
		DrawQuad(position, size, color, s_Data->WhiteTexture);
	}

	void Renderer2D::DrawQuad(glm::vec2 const & position, glm::vec2 const & size, Ref<Texture2D> const & texture)
	{
		DrawQuad({position.x, position.y, 0.0f}, size, glm::vec4(1.0f), texture);
	}

	void Renderer2D::DrawQuad(glm::vec3 const & position, glm::vec2 const & size, Ref<Texture2D> const & texture)
	{
		DrawQuad(position, size, glm::vec4(1.0f), texture);
	}
	
	void Renderer2D::DrawQuad(glm::vec2 const & position, glm::vec2 const & size, glm::vec4 const & color, Ref<Texture2D> const & texture)
	{
		DrawQuad({position.x, position.y, 0.0f}, size, color, texture);
	}

	void Renderer2D::DrawQuad(glm::vec3 const & position, glm::vec2 const & size, glm::vec4 const & color, Ref<Texture2D> const & texture)
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		texture->Bind(s_TextureSlot);

		s_Data->TextureShader->UploadUniformMat4("u_Transform", transform);
		s_Data->TextureShader->UploadUniformFloat4("u_Color", color);

		RendererCommand::DrawIndexed(s_Data->QuadVertexArray);
	}
}
