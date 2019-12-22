#include "Sandbox2D.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#if !defined(GES_BYPASS_VENDOR_HEADERS)
	#include <imgui.h>
#endif

static GES::Ref<GES::VertexArray> CreateVertexArraySquare()
{
	auto vertexArray = GES::VertexArray::Create();

	float vertices[] = {
		/*position*/ -0.5f, -0.5f, 0.0f,
		/*position*/  0.5f, -0.5f, 0.0f,
		/*position*/  0.5f,  0.5f, 0.0f,
		/*position*/ -0.5f,  0.5f, 0.0f,
	};
	auto vertexBuffer = GES::VertexBuffer::Create(vertices, sizeof(vertices));
	vertexBuffer->SetLayout({
		{ GES::ShaderDataType::Float3, "a_Position" },
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

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D")
	, m_CameraController(1280.0f / 720.0f)
{
}

void Sandbox2D::OnAttach()
{
	m_SquareVA = CreateVertexArraySquare();

	m_ShaderLibrary.Add(
		GES::Shader::CreatePath("assets/shaders/flat_color.glsl")
	);
}

void Sandbox2D::OnDetach()
{

}

void Sandbox2D::OnUpdate(GES::Timestep ts)
{
	// Update
	m_CameraController.OnUpdate(ts);

	// Render
	GES::Renderer::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
	GES::Renderer::Clear();

	GES::Renderer::BeginScene(m_CameraController.GetCamera());

	auto flatColorShader = m_ShaderLibrary.Get("flat_color");
	flatColorShader->Bind();
	flatColorShader->UploadUniformFloat4("u_Color", m_SquareColor);

	glm::mat4 square_transform = glm::scale(glm::mat4(1.0f), glm::vec3(1.5f));
	GES::Renderer::Submit(flatColorShader, m_SquareVA, square_transform);

	GES::Renderer::EndScene();
}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void Sandbox2D::OnEvent(GES::Event& e)
{
	m_CameraController.OnEvent(e);
}
