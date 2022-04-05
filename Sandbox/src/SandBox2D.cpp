#include "Sandbox2D.h"

#include "ImGui/imgui.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

Sandbox2D::Sandbox2D() : Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f) {	
}

void Sandbox2D::OnAttach() {
	m_Texture = Quiet::Texture2D::Create("res/textures/Checkerboard.png");
}

void Sandbox2D::OnDetach() {
	
}

void Sandbox2D::OnUpdate(Quiet::Timestep deltaTime) {
	// Update
	m_CameraController.OnUpdate(deltaTime);

	// Render
	Quiet::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
	Quiet::RenderCommand::Clear();
	
	Quiet::Renderer2D::BeginScene(m_CameraController.GetCamera());
	Quiet::Renderer2D::DrawQuad({ -1.0f,  0.0f }, { 0.8f, 0.8f  }, { 0.8f, 0.2f, 0.3f, 1.0f });
	Quiet::Renderer2D::DrawQuad({  0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
	Quiet::Renderer2D::DrawQuad({  0.0f,  0.0f, -0.1f }, { 5.0f, 5.0f }, m_Texture);
	Quiet::Renderer2D::EndScene();
}

void Sandbox2D::OnImGuiRender() {
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void Sandbox2D::OnEvent(Quiet::Event& event) {
	m_CameraController.OnEvent(event);
}
