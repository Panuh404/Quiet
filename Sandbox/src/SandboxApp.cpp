#include "Quiet.h"
#include "Quiet/Core/EntryPoint.h"

#include "Platform/OpenGL/OpenGLShader.h"

#include "ImGui/imgui.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "SandBox2D.h"

class ExampleLayer : public Quiet::Layer {
public:
	//ExampleLayer() : Layer("Example"), 
	//	m_CameraController(1280.0f / 720.0f) 
	//{
	//	////// Triangle /////
	//	m_TriangleVA = Quiet::VertexArray::Create();
	//	float triangleVertices[] = {
	//
	//		-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
	//		 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
	//		 0.0f,  0.5f, 0.0f, 0.8f, 0.7f, 0.2f, 1.0f
	//	};
	//	Quiet::Ref<Quiet::VertexBuffer> triangleVB;
	//	triangleVB = Quiet::VertexBuffer::Create(triangleVertices, sizeof(triangleVertices));
	//
	//	triangleVB->SetLayout({
	//		{ Quiet::ShaderDataType::Float3, "a_Position" },
	//		{ Quiet::ShaderDataType::Float4, "a_Color"}
	//		});
	//	m_TriangleVA->AddVertexBuffer(triangleVB);
	//
	//	uint32_t triangleIndices[3] = { 0, 1, 2 };
	//	Quiet::Ref<Quiet::IndexBuffer> triangleIB;
	//	triangleIB = Quiet::IndexBuffer::Create(triangleIndices, sizeof(triangleIndices) / sizeof(uint32_t));
	//	m_TriangleVA->SetIndexBuffer(triangleIB);
	//	
	//	///// Square /////
	//	m_SquareVA = Quiet::VertexArray::Create();
	//	float squareVertices[] = {
	//		//Square Coord      //Tex Coord
	//		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
	//		 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
	//		 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
	//		-0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
	//	};
	//	Quiet::Ref<Quiet::VertexBuffer> squareVB;
	//	squareVB = Quiet::VertexBuffer::Create(squareVertices, sizeof(squareVertices));
	//
	//	squareVB->SetLayout({
	//		{ Quiet::ShaderDataType::Float3, "a_Position" },
	//		{ Quiet::ShaderDataType::Float2, "a_TexCoord" }
	//	});
	//	m_SquareVA->AddVertexBuffer(squareVB);
	//
	//	uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
	//	Quiet::Ref<Quiet::IndexBuffer> squareIB;
	//	squareIB = Quiet::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
	//	m_SquareVA->SetIndexBuffer(squareIB);
	//	
	//	// Shader Handling
	//	m_FlatColorShader = Quiet::Shader::Create("res/shaders/FlatColor.glsl");
	//	auto m_TextureShader = m_ShaderLibrary.Load("res/shaders/Texture.glsl");
	//	
	//	m_TexBoard = Quiet::Texture2D::Create("res/textures/Checkerboard.png");
	//	m_TexFace = Quiet::Texture2D::Create("res/textures/awesomeface.png");
	//
	//	std::dynamic_pointer_cast<Quiet::OpenGLShader>(m_TextureShader)->Bind();
	//	std::dynamic_pointer_cast<Quiet::OpenGLShader>(m_TextureShader)->UploadUniformInt("u_Texture", 0);
	//}
	
	void OnUpdate(Quiet::Timestep deltaTime) override {
		// Update
		m_CameraController.OnUpdate(deltaTime);

		//Render
		Quiet::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		Quiet::RenderCommand::Clear();
		
		Quiet::Renderer::BeginScene(m_CameraController.GetCamera());
		
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
		auto textureShader = m_ShaderLibrary.Get("Texture");
		
		m_TexBoard->Bind(); Quiet::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
		m_TexFace->Bind(); Quiet::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
		Quiet::Renderer::EndScene();
	}
	
	void OnImGuiRender() override {
		ImGui::Begin("Settings");
		ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}
	
	void OnEvent(Quiet::Event& event) override {
		m_CameraController.OnEvent(event);
		
		if (event.GetEventType() == Quiet::EventType::WindowResize) {
			auto& resizeEvent = dynamic_cast<Quiet::WindowResizeEvent&>(event);
			resizeEvent.GetWidth();
			resizeEvent.GetHeight();
						
		}
	}
	
	bool OnKeyPressedEvent(Quiet::KeyPressedEvent& event) {
		
		return false;
	}
	
private:
	Quiet::ShaderLibrary m_ShaderLibrary;

	Quiet::Ref<Quiet::Shader> m_FlatColorShader;
	Quiet::Ref<Quiet::VertexArray> m_TriangleVA, m_SquareVA;
	Quiet::Ref<Quiet::Texture2D> m_TexBoard, m_TexFace;

	Quiet::OrthographicCameraController m_CameraController;
	glm::vec3 m_SquareColor = {0.2f, 0.3f, 0.8f};
};

class Sandbox : public Quiet::Application {
public:
	Sandbox() {
		// PushLayer(new ExampleLayer());
		PushLayer(new Sandbox2D());
	}
	
	~Sandbox() {}
};

Quiet::Application* Quiet::CreateApplication() {
	return new Sandbox();
}