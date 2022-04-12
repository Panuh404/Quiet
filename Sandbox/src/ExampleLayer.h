#pragma once

#include "Quiet.h"

class ExampleLayer : public Quiet::Layer
{
public:
	ExampleLayer();
	virtual ~ExampleLayer() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;
	
	void OnUpdate(Quiet::Timestep deltaTime) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Quiet::Event& event) override;

private:
	Quiet::ShaderLibrary m_ShaderLibrary;
	Quiet::OrthographicCameraController m_CameraController;

	Quiet::Ref<Quiet::Shader> m_FlatColorShader;
	Quiet::Ref<Quiet::VertexArray> m_TriangleVA, m_SquareVA;
	Quiet::Ref<Quiet::Texture2D> m_TexBoard, m_TexFace;
	
	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
};