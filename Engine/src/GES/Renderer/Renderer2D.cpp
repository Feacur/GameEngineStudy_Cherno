#include "ges_pch.h"
#include "Renderer2D.h"

#include "RendererCommand.h"
#include "Shader.h"
#include "Texture.h"
#include "Buffer.h"
#include "VertexArray.h"

#include "GES/Utils/Orthographic2dCamera.h"

#include "GES/Debug/Instrumentor.h"
#include "GES/Debug/Code.h"

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
	static u32 const s_TextureSlot = 0;

	static Ref<VertexArray> CreateQuadVertexArray()
	{
		GES_PROFILE_FUNCTION();
		auto vertexArray = VertexArray::Create();

		r32 vertices[] = {
			/*position*/ -0.5f, -0.5f, 0.0f, /*UV*/ 0.0f, 0.0f,
			/*position*/  0.5f, -0.5f, 0.0f, /*UV*/ 1.0f, 0.0f,
			/*position*/  0.5f,  0.5f, 0.0f, /*UV*/ 1.0f, 1.0f,
			/*position*/ -0.5f,  0.5f, 0.0f, /*UV*/ 0.0f, 1.0f,
		};
		auto vertexBuffer = VertexBuffer::Create(vertices, C_ARRAY_LENGTH(vertices));
		vertexBuffer->SetLayout({
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float2, "a_TexCoord" },
		});
		vertexArray->AddVertexBuffer(vertexBuffer);

		u32 indices[] = {
			0, 1, 2,
			2, 3, 0,
		};
		auto indexBuffer = IndexBuffer::Create(indices, C_ARRAY_LENGTH(indices));
		vertexArray->SetIndexBuffer(indexBuffer);
		
		return vertexArray;
	}
	
	void Renderer2D::Init()
	{
		GES_PROFILE_FUNCTION();
		s_Data = new Data();
		s_Data->QuadVertexArray = CreateQuadVertexArray();
		s_Data->TextureShader = GES::Shader::CreatePath("assets/shaders/renderer2d.glsl");
		
		u32 whiteTextureData = 0xffffffff;
		s_Data->WhiteTexture = Texture2D::CreateRaw(1u, 1u);
		s_Data->WhiteTexture->SetData(&whiteTextureData, sizeof(whiteTextureData));

		s_Data->TextureShader->Bind();
		s_Data->TextureShader->UploadUniformInt("u_Texture", (s32)s_TextureSlot);
	}
	
	void Renderer2D::Shutdown()
	{
		GES_PROFILE_FUNCTION();
		delete s_Data;
	}

	void Renderer2D::BeginScene(Orthographic2dCamera const & camera)
	{
		GES_PROFILE_FUNCTION();
		s_Data->TextureShader->Bind();
		s_Data->TextureShader->UploadUniformMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
		
		s_Data->QuadVertexArray->Bind();
	}

	void Renderer2D::EndScene()
	{
		GES_PROFILE_FUNCTION();
	}
	
	void Renderer2D::DrawQuad(glm::vec2 const & position, glm::vec2 const & size, r32 rotation, glm::vec4 const & color)
	{
		GES_PROFILE_FUNCTION();
		DrawQuad({position.x, position.y, 0.0f}, size, rotation, color, s_Data->WhiteTexture);
	}

	void Renderer2D::DrawQuad(glm::vec3 const & position, glm::vec2 const & size, r32 rotation, glm::vec4 const & color)
	{
		GES_PROFILE_FUNCTION();
		DrawQuad(position, size, rotation, color, s_Data->WhiteTexture);
	}

	void Renderer2D::DrawQuad(glm::vec2 const & position, glm::vec2 const & size, r32 rotation, Ref<Texture2D> const & texture)
	{
		GES_PROFILE_FUNCTION();
		DrawQuad({position.x, position.y, 0.0f}, size, rotation, glm::vec4(1.0f), texture);
	}

	void Renderer2D::DrawQuad(glm::vec3 const & position, glm::vec2 const & size, r32 rotation, Ref<Texture2D> const & texture)
	{
		GES_PROFILE_FUNCTION();
		DrawQuad(position, size, rotation, glm::vec4(1.0f), texture);
	}
	
	void Renderer2D::DrawQuad(glm::vec2 const & position, glm::vec2 const & size, r32 rotation, glm::vec4 const & color, Ref<Texture2D> const & texture)
	{
		GES_PROFILE_FUNCTION();
		DrawQuad({position.x, position.y, 0.0f}, size, rotation, color, texture);
	}

	void Renderer2D::DrawQuad(glm::vec3 const & position, glm::vec2 const & size, r32 rotation, glm::vec4 const & color, Ref<Texture2D> const & texture)
	{
		GES_PROFILE_FUNCTION();
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::rotate(glm::mat4(1.0f), rotation, { 0.0f, 0.0f, 1.0f })
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		texture->Bind(s_TextureSlot);

		s_Data->TextureShader->UploadUniformMat4("u_Transform", transform);
		s_Data->TextureShader->UploadUniformFloat4("u_Color", color);

		RendererCommand::DrawIndexed(s_Data->QuadVertexArray);
	}

	void Renderer2D::DrawPost(Ref<Shader> const & shader, glm::vec2 const & screenSize, glm::vec4 const & color)
	{
		GES_PROFILE_FUNCTION();

		shader->Bind();
		shader->UploadUniformFloat2("u_ScreenSize", screenSize);
		shader->UploadUniformFloat4("u_Color", color);

		RendererCommand::DrawTriangle(); // assuming [VERTEX_MODE == 1]
		// RendererCommand::DrawIndexed(s_Data->QuadVertexArray);
	}

	void Renderer2D::DrawPost(Ref<Shader> const & shader, glm::vec2 const & screenSize, glm::vec4 const & color, Ref<Texture2D> const & texture)
	{
		GES_PROFILE_FUNCTION();

		texture->Bind(s_TextureSlot);

		shader->Bind();
		shader->UploadUniformFloat2("u_ScreenSize", screenSize);
		shader->UploadUniformFloat4("u_Color", color);
		shader->UploadUniformInt("u_Texture", (s32)s_TextureSlot);

		RendererCommand::DrawTriangle(); // assuming [VERTEX_MODE == 1]
		// RendererCommand::DrawIndexed(s_Data->QuadVertexArray);
	}
}
