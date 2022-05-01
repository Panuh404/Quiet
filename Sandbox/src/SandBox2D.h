#pragma once

#include "Quiet.h"

#include "ParticleSystem.h"

class Sandbox2D : public Quiet::Layer
{
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

	Quiet::Ref<Quiet::Texture2D> m_CheckerboadTex;
	Quiet::Ref<Quiet::Texture2D> m_SpriteSheet;
	Quiet::Ref<Quiet::SubTexture2D> m_TextureStairs;
	Quiet::Ref<Quiet::SubTexture2D> m_TextureBarrel;
	Quiet::Ref<Quiet::SubTexture2D> m_TextureTree;


	float m_Rotation1 = -45.0f;
	float m_Rotation2 = -75.0f;

	glm::vec4 m_SquareColor1 = { 0.2f, 0.3f, 0.8f, 1.0f};
	glm::vec4 m_SquareColor2 = { 0.8f, 0.2f, 0.3f, 1.0f };
	glm::vec4 m_SquareColor3 = { 0.3f, 0.8f, 0.2f, 1.0f };

	ParticleSystem m_ParticleSystem;
	ParticleProps m_Particle;

};