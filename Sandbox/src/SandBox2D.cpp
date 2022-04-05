#include "Sandbox2D.h"

#include "ImGui/imgui.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "Platform/OpenGL/OpenGLShader.h"

Sandbox2D::Sandbox2D() : Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f) {	
}

void Sandbox2D::OnAttach() {
	m_VertexArray = Quiet::VertexArray::Create();

	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.5f,  0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f
	};
	
	Quiet::Ref<Quiet::VertexBuffer> vertexBuffer;
	vertexBuffer = Quiet::VertexBuffer::Create(vertices, sizeof(vertices));
	vertexBuffer->SetLayout({
		{ Quiet::ShaderDataType::Float3, "a_Position" }
	});
	m_VertexArray->AddVertexBuffer(vertexBuffer);

	uint32_t indices[6] = { 0, 1, 2, 2, 3, 0 };
	Quiet::Ref<Quiet::IndexBuffer> indexBuffer;
	indexBuffer = Quiet::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
	m_VertexArray->SetIndexBuffer(indexBuffer);

	m_FlatColorShader = Quiet::Shader::Create("res/shaders/FlatColor.glsl");
}

void Sandbox2D::OnDetach() {
	
}

void Sandbox2D::OnUpdate(Quiet::Timestep deltaTime) {
	// Update
	m_CameraController.OnUpdate(deltaTime);

	// Render
	Quiet::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
	Quiet::RenderCommand::Clear();
	
	Quiet::Renderer::BeginScene(m_CameraController.GetCamera());

	std::dynamic_pointer_cast<Quiet::OpenGLShader>(m_FlatColorShader)->Bind();
	std::dynamic_pointer_cast<Quiet::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat4("u_Color", m_SquareColor);

	Quiet::Renderer::Submit(m_FlatColorShader, m_VertexArray), glm::scale( glm::mat4(1.0f), glm::vec3(1.5f) );
	Quiet::Renderer::EndScene();
}

void Sandbox2D::OnImGuiRender() {
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void Sandbox2D::OnEvent(Quiet::Event& event) {
	m_CameraController.OnEvent(event);
}
