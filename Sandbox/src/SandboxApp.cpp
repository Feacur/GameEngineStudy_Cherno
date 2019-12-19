#include "GES.h"

#include <glm/gtc/matrix_transform.hpp>

class ExampleLayer : public GES::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
		, m_Camera(-1.6f, 1.6f, -0.9f, 0.9f)
	{
		CreateVertexArrayTriangle();
		CreateVertexArraySquare();

		m_ShaderLibrary.Add(
			GES::Shader::CreatePath("assets/shaders/vertex_color.glsl")
		);
		m_ShaderLibrary.Add(
			GES::Shader::CreatePath("assets/shaders/texture.glsl")
		);

		m_TextureCheckerboard = GES::Texture2D::Create("assets/textures/checkerboard.png");
		m_TextureChernoLogo = GES::Texture2D::Create("assets/textures/cherno_logo.png");
	}

	void OnUpdate(GES::Timestep ts) override
	{
		static glm::mat4 const identity = glm::mat4(1.0f);

		UpdateCamera(ts);

		GES::Renderer::SetClearColor();
		GES::Renderer::Clear();

		GES::Renderer::BeginScene(m_Camera);

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

	void OnImGuiRender() override
	{
	}

	void OnEvent(GES::Event & e) override
	{
	}

private:
	void UpdateCamera(GES::Timestep ts)
	{
		float positionDelta = m_CameraPositionSpeed * ts;
		float rotationDelta = m_CameraRotationSpeed * ts;

		auto cameraPosition = m_Camera.GetPosition();
		auto cameraRotation = m_Camera.GetRotation();

		if (GES::Input::IsKeyPressed(GES_KEY_A)) {
			cameraPosition.x -= positionDelta;
		}

		if (GES::Input::IsKeyPressed(GES_KEY_D)) {
			cameraPosition.x += positionDelta;
		}

		if (GES::Input::IsKeyPressed(GES_KEY_S)) {
			cameraPosition.y -= positionDelta;
		}

		if (GES::Input::IsKeyPressed(GES_KEY_W)) {
			cameraPosition.y += positionDelta;
		}

		if (GES::Input::IsKeyPressed(GES_KEY_Q)) {
			cameraRotation -= rotationDelta;
		}

		if (GES::Input::IsKeyPressed(GES_KEY_E)) {
			cameraRotation += rotationDelta;
		}

		m_Camera.SetPosition(cameraPosition);
		m_Camera.SetRotation(cameraRotation);
		
		m_Camera.RecalculateViewMatrix();
	}

	void CreateVertexArrayTriangle()
	{
		m_VertexArrayTriangle = GES::VertexArray::Create();
		GES::Ref<GES::VertexArray> & vertexArray = m_VertexArrayTriangle;

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
	}

	void CreateVertexArraySquare()
	{
		m_VertexArraySquare = GES::VertexArray::Create();
		GES::Ref<GES::VertexArray> & vertexArray = m_VertexArraySquare;

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
	}

private:
	GES::ShaderLibrary m_ShaderLibrary;
	GES::Ref<GES::VertexArray> m_VertexArrayTriangle;
	GES::Ref<GES::VertexArray> m_VertexArraySquare;
	GES::Ref<GES::Texture> m_TextureCheckerboard;
	GES::Ref<GES::Texture> m_TextureChernoLogo;

	GES::Orthographic2dCamera m_Camera;
	float m_CameraPositionSpeed = 1;
	float m_CameraRotationSpeed = 1;
};

class Sandbox : public GES::Application
{
public:
	Sandbox()
	{
		ImGui::SetCurrentContext(GetImGuiContext());
		PushLayer(new ExampleLayer());
	}
};

GES::Ref<GES::Application> GES::CreateApplication()
{
	return GES::CreateRef<Sandbox>();
}
