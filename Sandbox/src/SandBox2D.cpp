#include "Sandbox2D.h"
#include <ImGui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Sandbox2D::Sandbox2D() : Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f) {	
}

void Sandbox2D::OnAttach() {
	QUIET_PROFILE_FUNCTION();
	m_Texture = Quiet::Texture2D::Create("res/textures/Checkerboard.png");
}

void Sandbox2D::OnDetach() {
	QUIET_PROFILE_FUNCTION();
}

void Sandbox2D::OnUpdate(Quiet::Timestep deltaTime) {
	QUIET_PROFILE_FUNCTION();	
	// Update
	m_CameraController.OnUpdate(deltaTime);

	// Render
	{
		QUIET_PROFILE_SCOPE("Renderer Pref");
		Quiet::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Quiet::RenderCommand::Clear();
	}
	// Draw
	{
		static float rotation = 0.0f;
		rotation += deltaTime * 20.0f;

		QUIET_PROFILE_SCOPE("Renderer Draw");
		Quiet::Renderer2D::BeginScene(m_CameraController.GetCamera());
		Quiet::Renderer2D::DrawQuad({  0.5f, -0.5f }, { 0.5f, 0.75f }, { m_SquareColor1 });
		Quiet::Renderer2D::DrawQuad({ -1.0f,  0.0f }, { 0.8f, 0.8f  }, { m_SquareColor2 });
		Quiet::Renderer2D::DrawQuadRotated({  1.5f, -0.5f }, { 0.5f, 0.75f }, rotation, { m_SquareColor3 });
		Quiet::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 10.0f, 10.0f }, m_Texture, 10.0f);
		Quiet::Renderer2D::DrawQuadRotated({ -2.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }, m_Rotation1, m_Texture, 20.0f);
		Quiet::Renderer2D::EndScene();
	}
}

void Sandbox2D::OnImGuiRender() {
	QUIET_PROFILE_FUNCTION();
	ImGui::Begin("Settings");
	ImGui::Text("COLORS");
	ImGui::SliderFloat("Rotation 1", &m_Rotation1, -360, 360);
	ImGui::SliderFloat("Rotation 2", &m_Rotation2, -360, 360);
	ImGui::ColorEdit4("Color 1", glm::value_ptr(m_SquareColor1));
	ImGui::ColorEdit4("Color 2", glm::value_ptr(m_SquareColor2));
	ImGui::ColorEdit4("Color 3", glm::value_ptr(m_SquareColor3));
	ImGui::End();
}

void Sandbox2D::OnEvent(Quiet::Event& event) {
	m_CameraController.OnEvent(event);
}
