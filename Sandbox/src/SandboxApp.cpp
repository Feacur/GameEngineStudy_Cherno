#include "GES.h"

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

		const char * vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjectionMatrix;

 			out vec3 v_Position;
 			out vec4 v_Color;
			
 			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjectionMatrix * vec4(a_Position, 1.0);
			}
		)";

 		const char * fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			
 			in vec3 v_Position;
 			in vec4 v_Color;

 			void main()
			{
				color = v_Color;
			}
		)";

 		m_Shader.reset(new GES::Shader(vertexSrc, fragmentSrc));
	}

	void OnUpdate() override
	{
		m_Camera.SetRotation(45);
		m_Camera.RecalculateViewMatrix();

		GES::Renderer::SetClearColor();
		GES::Renderer::Clear();

		GES::Renderer::BeginScene(m_Camera);

		GES::Renderer::Submit(m_Shader, m_VertexArray);

		GES::Renderer::EndScene();
	}

	void OnImGuiRender() override
	{
	}

	void OnEvent(GES::Event& event) override
	{
	}

private:
	std::shared_ptr<GES::VertexArray> m_VertexArray;
	std::shared_ptr<GES::Shader> m_Shader;

	GES::Orthographic2dCamera m_Camera;
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
