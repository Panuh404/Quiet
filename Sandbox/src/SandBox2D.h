#pragma once

#include "Quiet.h"

class Sandbox2D : public Quiet::Layer {
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Quiet::Timestep deltaTime) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Quiet::Event& event) override;

private:
	Quiet::OrthographicCameraController m_CameraController;
	// Temp
	Quiet::Ref<Quiet::VertexArray> m_VertexArray;
	Quiet::Ref<Quiet::Shader> m_FlatColorShader;
	Quiet::Ref<Quiet::Texture2D> m_Texture;
	
	glm::vec4 m_SquareColor1 = { 0.2f, 0.3f, 0.8f, 1.0f};
	glm::vec4 m_SquareColor2 = { 0.8f, 0.2f, 0.3f, 1.0f };
};