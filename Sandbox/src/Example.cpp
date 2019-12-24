#include "Example.h"

#include <glm/gtc/matrix_transform.hpp>

#include <imgui.h>

static GES::Ref<GES::VertexArray> CreateVertexArrayTriangle()
{
	GES_PROFILE_FUNCTION();
	auto vertexArray = GES::VertexArray::Create();

	float vertices[] = {
		/*position*/ -0.5f, -0.5f, 0.0f, /*color*/ 1.0f, 0.0f, 0.0f, 1.0f,
		/*position*/  0.5f, -0.5f, 0.0f, /*color*/ 0.0f, 1.0f, 0.0f, 1.0f,
		/*position*/  0.0f,  0.5f, 0.0f, /*color*/ 0.0f, 0.0f, 1.0f, 1.0f,
	};
	auto vertexBuffer = GES::VertexBuffer::Create(vertices, sizeof(vertices));
	vertexBuffer->SetLayout({
		{ GES::ShaderDataType::Float3, "a_Position" },
		{ GES::ShaderDataType::Float4, "a_Color" },
	});
	vertexArray->AddVertexBuffer(vertexBuffer);

	uint32 indices[] = {
		0, 1, 2,
	};
	auto indexBuffer = GES::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32));
	vertexArray->SetIndexBuffer(indexBuffer);

	return vertexArray;
}

static GES::Ref<GES::VertexArray> CreateVertexArraySquare()
{
	GES_PROFILE_FUNCTION();
	auto vertexArray = GES::VertexArray::Create();

	float vertices[] = {
		/*position*/ -0.5f, -0.5f, 0.0f, /*UV*/ 0.0f, 0.0f,
		/*position*/  0.5f, -0.5f, 0.0f, /*UV*/ 1.0f, 0.0f,
		/*position*/  0.5f,  0.5f, 0.0f, /*UV*/ 1.0f, 1.0f,
		/*position*/ -0.5f,  0.5f, 0.0f, /*UV*/ 0.0f, 1.0f,
	};
	auto vertexBuffer = GES::VertexBuffer::Create(vertices, sizeof(vertices));
	vertexBuffer->SetLayout({
		{ GES::ShaderDataType::Float3, "a_Position" },
		{ GES::ShaderDataType::Float2, "a_TexCoord" },
	});
	vertexArray->AddVertexBuffer(vertexBuffer);

	uint32 indices[] = {
		0, 1, 2,
		2, 3, 0,
	};
	auto indexBuffer = GES::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32));
	vertexArray->SetIndexBuffer(indexBuffer);
	
	return vertexArray;
}

ExampleLayer::ExampleLayer()
	: Layer("Example")
	, m_CameraController(1280.0f / 720.0f)
{
	GES_PROFILE_FUNCTION();
	m_VertexArrayTriangle = CreateVertexArrayTriangle();
	m_VertexArraySquare = CreateVertexArraySquare();

	m_ShaderLibrary.Add(
		GES::Shader::CreatePath("assets/shaders/vertex_color.glsl")
	);
	m_ShaderLibrary.Add(
		GES::Shader::CreatePath("assets/shaders/texture.glsl")
	);

	m_TextureCheckerboard = GES::Texture2D::Create("assets/textures/checkerboard.png");
	m_TextureChernoLogo = GES::Texture2D::Create("assets/textures/cherno_logo.png");
}

void ExampleLayer::OnUpdate(GES::Timestep ts)
{
	GES_PROFILE_FUNCTION();
	static glm::mat4 const identity = glm::mat4(1.0f);

	m_CameraController.OnUpdate(ts);

	GES::RendererCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
	GES::RendererCommand::Clear();

	GES::Renderer::BeginScene(m_CameraController.GetCamera());

	auto shaderVertexColor = m_ShaderLibrary.Get("vertex_color");
	glm::mat4 triangle_scale = glm::scale(identity, glm::vec3(0.1f));
	for (int y = -10; y < 10; y++)
	{
		for (int x = -10; x < 10; x++)
		{
			glm::vec3 triangle_pos(x * 0.11f, y * 0.11f, 0.0f);
			glm::mat4 triangle_transform = glm::translate(identity, triangle_pos) * triangle_scale;
			GES::Renderer::Submit(shaderVertexColor, m_VertexArrayTriangle, triangle_transform);
		}
	}

	auto shaderTexture = m_ShaderLibrary.Get("texture");
	glm::mat4 square_scale = glm::scale(identity, glm::vec3(1.5f));
	glm::vec3 square_pos(0.0f, 0.0f, 0.0f);
	glm::mat4 square_transform = glm::translate(identity, square_pos) * square_scale;
	GES::Renderer::Submit(shaderTexture, m_VertexArraySquare, square_transform, m_TextureChernoLogo);

	GES::Renderer::EndScene();
}

void ExampleLayer::OnImGuiRender()
{
	GES_PROFILE_FUNCTION();
}

void ExampleLayer::OnEvent(GES::Event & e)
{
	GES_PROFILE_FUNCTION();
	m_CameraController.OnEvent(e);
}
