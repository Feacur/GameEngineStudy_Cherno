#include "GES.h"

#include <glm/gtc/matrix_transform.hpp>

class ExampleLayer : public GES::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
		, m_Camera(-1.6f, 1.6f, -0.9f, 0.9f)
	{
		m_VertexArray.reset(GES::VertexArray::Create());

		float vertices[] = {
			/*position*/ -0.5f, -0.5f, 0.0f, /*color*/ 1.0f, 0.0f, 0.0f, 1.0f,
			/*position*/  0.5f, -0.5f, 0.0f, /*color*/ 0.0f, 1.0f, 0.0f, 1.0f,
			/*position*/  0.0f,  0.5f, 0.0f, /*color*/ 0.0f, 0.0f, 1.0f, 1.0f,
		};
		std::shared_ptr<GES::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(GES::VertexBuffer::Create(vertices, sizeof(vertices)));
		vertexBuffer->SetLayout({
			{ GES::ShaderDataType::Float3, "a_Position" },
			{ GES::ShaderDataType::Float4, "a_Color" },
		});
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32 indices[] = { 0, 1, 2, };
		std::shared_ptr<GES::IndexBuffer> indexBuffer;
		indexBuffer.reset(GES::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		cstring vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjectionMatrix;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;
			
			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjectionMatrix * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		cstring fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			
			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = v_Color;
			}
		)";

		m_Shader.reset(GES::Shader::Create(vertexSrc, fragmentSrc));
	}

	void OnUpdate(GES::Timestep ts) override
	{
		UpdateCamera(ts);

		GES::Renderer::SetClearColor();
		GES::Renderer::Clear();

		GES::Renderer::BeginScene(m_Camera);

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));
		for (int y = -10; y < 10; y++)
		{
			for (int x = -10; x < 10; x++)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				GES::Renderer::Submit(m_Shader, m_VertexArray, transform);
			}
		}

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

private:
	std::shared_ptr<GES::VertexArray> m_VertexArray;
	std::shared_ptr<GES::Shader> m_Shader;

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

GES::Application *GES::CreateApplication()
{
	return new Sandbox();
}
