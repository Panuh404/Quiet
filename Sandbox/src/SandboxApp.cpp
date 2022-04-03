#include "Quiet.h"

#include "Platform/OpenGL/OpenGLShader.h"

#include "ImGui/imgui.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

class ExampleLayer : public Quiet::Layer {
public:
	ExampleLayer() : Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9, 0.9f) {
		/////////////////////
		////// Triangle /////
		/////////////////////
		m_TriangleVA.reset(Quiet::VertexArray::Create());
		float triangleVertices[] = {

			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.7f, 0.2f, 1.0f
		};
		Quiet::Ref<Quiet::VertexBuffer> triangleVB;
		triangleVB.reset(Quiet::VertexBuffer::Create(triangleVertices, sizeof(triangleVertices)));

		triangleVB->SetLayout({
			{ Quiet::ShaderDataType::Float3, "a_Position" },
			{ Quiet::ShaderDataType::Float4, "a_Color"}
			});
		m_TriangleVA->AddVertexBuffer(triangleVB);

		uint32_t triangleIndices[3] = { 0, 1, 2 };
		Quiet::Ref<Quiet::IndexBuffer> triangleIB;
		triangleIB.reset(Quiet::IndexBuffer::Create(triangleIndices, sizeof(triangleIndices) / sizeof(uint32_t)));
		m_TriangleVA->SetIndexBuffer(triangleIB);
		
		//////////////////
		///// Square /////
		/////////////////////
		m_SquareVA.reset(Quiet::VertexArray::Create());
		float squareVertices[] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f
		};
		Quiet::Ref<Quiet::VertexBuffer> squareVB;
		squareVB.reset(Quiet::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

		squareVB->SetLayout({
			{ Quiet::ShaderDataType::Float3, "a_Position" }
			});
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		Quiet::Ref<Quiet::IndexBuffer> squareIB;
		squareIB.reset(Quiet::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

		std::string vertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;
			

			out vec3 v_Position;
			out vec4 v_Color;

			void main(){
				v_Color = a_Color;
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			} )";

		std::string fragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;		
			in vec4 v_Color;


			void main(){
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			} )";

		std::string FlatColorVertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;
			
			out vec3 v_Position;

			void main(){
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			} )";

		std::string FlatColorFragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			uniform vec3 u_Color;

			in vec3 v_Position;	

			void main(){
				color = vec4(u_Color, 1.0);
			} )";

		m_Shader.reset(Quiet::Shader::Create(vertexSrc, fragmentSrc));
		m_FlatColorShader.reset(Quiet::Shader::Create(FlatColorVertexSrc, FlatColorFragmentSrc));
	}
	
	void OnUpdate(Quiet::Timestep deltaTime) override {
		// Camera Movement
		if (Quiet::Input::IsKeyPressed(Quiet::Key::Left))
			m_CameraPosition.x += m_CameraMoveSpeed * deltaTime;
		else if (Quiet::Input::IsKeyPressed(Quiet::Key::Right))
			m_CameraPosition.x -= m_CameraMoveSpeed * deltaTime;
		
		if (Quiet::Input::IsKeyPressed(Quiet::Key::Up))
			m_CameraPosition.y -= m_CameraMoveSpeed * deltaTime;
		else if (Quiet::Input::IsKeyPressed(Quiet::Key::Down))
			m_CameraPosition.y += m_CameraMoveSpeed * deltaTime;

		// Camera Rotation
		if (Quiet::Input::IsKeyPressed(Quiet::Key::Q))
			m_CameraRotation -= m_CameraRotationSpeed * deltaTime;
		else if (Quiet::Input::IsKeyPressed(Quiet::Key::E))
			m_CameraRotation += m_CameraRotationSpeed * deltaTime;
		
		Quiet::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		Quiet::RenderCommand::Clear();

		m_Camera.SetPosition( m_CameraPosition );
		m_Camera.SetRotation( m_CameraRotation );

		Quiet::Renderer::BeginScene(m_Camera);
		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		std::dynamic_pointer_cast<Quiet::OpenGLShader>(m_FlatColorShader)->Bind();
		std::dynamic_pointer_cast<Quiet::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("u_Color", m_SquareColor);
		
		for (int y = 0; y < 20; y++) {
			for (int x = 0; x < 20; x++) {
				glm::vec3 position(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * scale;
				Quiet::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
			}
		}
		Quiet::Renderer::Submit(m_Shader, m_TriangleVA);

		Quiet::Renderer::EndScene();
	}
	
	void OnImGuiRender() override {
		ImGui::Begin("Settings");
		ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}
	
	void OnEvent(Quiet::Event& event) override {
		Quiet::EventDispatcher dispatcher(event);
		dispatcher.Dispatch<Quiet::KeyPressedEvent>(QUIET_BIND_EVENT_FN(ExampleLayer::OnKeyPressedEvent));
	}
	
	bool OnKeyPressedEvent(Quiet::KeyPressedEvent& event) {
		
		return false;
	}
	
private:
	Quiet::Ref<Quiet::Shader> m_Shader;
	Quiet::Ref<Quiet::VertexArray> m_TriangleVA;

	Quiet::Ref<Quiet::Shader> m_FlatColorShader;
	Quiet::Ref<Quiet::VertexArray> m_SquareVA;

	Quiet::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition = {0.0f, 0.0f, 0.0f};
	float m_CameraRotation = 0.0f;
	
	float m_CameraMoveSpeed = 1.0f;
	float m_CameraRotationSpeed = 1.0f;

	glm::vec3 m_SquareColor = {0.2f, 0.3f, 0.8f};
};

class Sandbox : public Quiet::Application {
public:
	Sandbox() {
		PushLayer(new ExampleLayer());
	}
	
	~Sandbox() {

	}
};

Quiet::Application* Quiet::CreateApplication() {
	return new Sandbox();
}