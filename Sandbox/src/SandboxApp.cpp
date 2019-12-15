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

		CreateShaderProgramVertexColor();
		CreateShaderProgramTexture();

		m_Texture.reset(GES::Texture2D::Create("assets/textures/checkerboard.png"));
	}

	void OnUpdate(GES::Timestep ts) override
	{
		static glm::mat4 const identity = glm::mat4(1.0f);

		UpdateCamera(ts);

		GES::Renderer::SetClearColor();
		GES::Renderer::Clear();

		GES::Renderer::BeginScene(m_Camera);

		glm::mat4 triangle_scale = glm::scale(identity, glm::vec3(0.1f));
		for (int y = -10; y < 10; y++)
		{
			for (int x = -10; x < 10; x++)
			{
				glm::vec3 triangle_pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 triangle_transform = glm::translate(identity, triangle_pos) * triangle_scale;
				GES::Renderer::Submit(m_ShaderVertexColor, m_VertexArrayTriangle, triangle_transform);
			}
		}

		m_Texture->Bind(0u);
		glm::mat4 square_scale = glm::scale(identity, glm::vec3(1.5f));
		glm::vec3 square_pos(0.0f, 0.0f, 0.0f);
		glm::mat4 square_transform = glm::translate(identity, square_pos) * square_scale;
		GES::Renderer::Submit(m_ShaderTexture, m_VertexArraySquare, square_transform, m_Texture);

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
		GES::Ref<GES::VertexArray> & vertexArray = m_VertexArrayTriangle;
		vertexArray.reset(GES::VertexArray::Create());

		float vertices[] = {
			/*position*/ -0.5f, -0.5f, 0.0f, /*color*/ 1.0f, 0.0f, 0.0f, 1.0f,
			/*position*/  0.5f, -0.5f, 0.0f, /*color*/ 0.0f, 1.0f, 0.0f, 1.0f,
			/*position*/  0.0f,  0.5f, 0.0f, /*color*/ 0.0f, 0.0f, 1.0f, 1.0f,
		};
		GES::Ref<GES::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(GES::VertexBuffer::Create(vertices, sizeof(vertices)));
		vertexBuffer->SetLayout({
			{ GES::ShaderDataType::Float3, "a_Position" },
			{ GES::ShaderDataType::Float4, "a_Color" },
		});
		vertexArray->AddVertexBuffer(vertexBuffer);

		uint32 indices[] = { 0, 1, 2, };
		GES::Ref<GES::IndexBuffer> indexBuffer;
		indexBuffer.reset(GES::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32)));
		vertexArray->SetIndexBuffer(indexBuffer);
	}

	void CreateVertexArraySquare()
	{
		GES::Ref<GES::VertexArray> & vertexArray = m_VertexArraySquare;
		vertexArray.reset(GES::VertexArray::Create());

		float vertices[] = {
			/*position*/ -0.5f, -0.5f, 0.0f, /*UV*/ 0.0f, 0.0f,
			/*position*/  0.5f, -0.5f, 0.0f, /*UV*/ 1.0f, 0.0f,
			/*position*/  0.5f,  0.5f, 0.0f, /*UV*/ 1.0f, 1.0f,
			/*position*/ -0.5f,  0.5f, 0.0f, /*UV*/ 0.0f, 1.0f,
		};
		GES::Ref<GES::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(GES::VertexBuffer::Create(vertices, sizeof(vertices)));
		vertexBuffer->SetLayout({
			{ GES::ShaderDataType::Float3, "a_Position" },
			{ GES::ShaderDataType::Float2, "a_TexCoord" },
		});
		vertexArray->AddVertexBuffer(vertexBuffer);

		uint32 indices[] = { 0, 1, 2, 2, 3, 0, };
		GES::Ref<GES::IndexBuffer> indexBuffer;
		indexBuffer.reset(GES::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32)));
		vertexArray->SetIndexBuffer(indexBuffer);
	}

	void CreateShaderProgramVertexColor()
	{
		GES::Ref<GES::Shader> & shader = m_ShaderVertexColor;

		cstring vertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjectionMatrix;
			uniform mat4 u_Transform;

			out vec4 v_Color;

			void main()
			{
				v_Color = a_Color;
				gl_Position = u_ViewProjectionMatrix * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		cstring fragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;
			
			in vec4 v_Color;

			void main()
			{
				color = v_Color;
			}
		)";

		shader.reset(GES::Shader::Create(vertexSrc, fragmentSrc));
	}

	void CreateShaderProgramTexture()
	{
		GES::Ref<GES::Shader> & shader = m_ShaderTexture;

		cstring vertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec2 a_TexCoord;

			uniform mat4 u_ViewProjectionMatrix;
			uniform mat4 u_Transform;

			out vec2 v_TexCoord;

			void main()
			{
				v_TexCoord = a_TexCoord;
				gl_Position = u_ViewProjectionMatrix * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		cstring fragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			uniform sampler2D u_Texture;

			in vec2 v_TexCoord;

			void main()
			{
				color = texture(u_Texture, v_TexCoord);
			}
		)";

		shader.reset(GES::Shader::Create(vertexSrc, fragmentSrc));
	}

private:
	GES::Ref<GES::VertexArray> m_VertexArrayTriangle;
	GES::Ref<GES::VertexArray> m_VertexArraySquare;
	GES::Ref<GES::Shader> m_ShaderVertexColor;
	GES::Ref<GES::Shader> m_ShaderTexture;
	GES::Ref<GES::Texture> m_Texture;

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
