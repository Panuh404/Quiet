#include "Sandbox2D.h"
#include <ImGui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

static uint32_t s_MapWidth = 20;
static const char* s_MapTiles =
"WWWWWWWWWWWWWWWWWWWW"
"WWWWWWWWWWWWWWWWWWWW"
"WWWWWDDDDWWWWWWWWWWW"
"WWWWWDDDDDDDWWWWWWWW"
"WWWDDDDDDDDDDWWWWWWW"
"WWDDDDDDDDDDDDDWWWWW"
"WDDDDWWWWWWWDDDWWWWW"
"WDDDWWWWCWWWWDDDWWWW"
"WWDDWWWWWWWWWDDDWWWW"
"WWDDWWWWWWWWWDDDWWWW"
"WWWDDDWWWWWWDDDWWWWW"
"WWWWWDDDDDDDDDWWWWWW"
"WWWWWWDDWWWWWWWWWWWW"
"WWWWWWWWWWWWWWWWWWWW"
;

Sandbox2D::Sandbox2D() : Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f) {	
}

void Sandbox2D::OnAttach() {
	QUIET_PROFILE_FUNCTION();
	// Textures
	m_CheckerboadTex = Quiet::Texture2D::Create("res/textures/Checkerboard.png");
	m_SpriteSheet = Quiet::Texture2D::Create("res/game/textures/RPG_sheet.png");

	// SubTextures
	m_TextureStairs = Quiet::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 7, 6 }, { 128,128 });
	m_TextureTree   = Quiet::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 2, 1 }, { 128,128 }, {1,2});

	m_MapWidth = s_MapWidth;
	m_MapHeight = strlen(s_MapTiles) / s_MapWidth;

	s_TextureMap['D'] = Quiet::SubTexture2D::CreateFromCoords(m_SpriteSheet, {6, 11}, {128,128});
	s_TextureMap['W'] = Quiet::SubTexture2D::CreateFromCoords(m_SpriteSheet, {11, 11}, {128,128});

	// Particle system Stuff
	m_Particle.ColorBegin = { 254 / 255.0f, 212 / 255.0f, 123 / 255.0f, 1.0f };
	m_Particle.ColorEnd = { 254 / 255.0f, 109 / 255.0f, 41 / 255.0f, 1.0f };
	m_Particle.SizeBegin = 0.5f, m_Particle.SizeVariation = 0.3f, m_Particle.SizeEnd = 0.0f;
	m_Particle.LifeTime = 1.0f;
	m_Particle.Velocity = { 0.0f, 0.0f };
	m_Particle.VelocityVariation = { 3.0f, 1.0f };
	m_Particle.Position = { 0.0f, 0.0f };

	m_CameraController.SetZoomLevel(5.0f);
}

void Sandbox2D::OnDetach() {
	QUIET_PROFILE_FUNCTION();
}

void Sandbox2D::OnUpdate(Quiet::Timestep deltaTime) {
	QUIET_PROFILE_FUNCTION();	
	// Update
	m_CameraController.OnUpdate(deltaTime);

	// Render
	Quiet::Renderer2D::ResetStats();
	{
		QUIET_PROFILE_SCOPE("Renderer Pref");
		Quiet::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Quiet::RenderCommand::Clear();
	}
	// Draw
	{
#if Demo_Scene
		static float rotation = 0.0f;
		rotation += deltaTime * 20.0f;

		QUIET_PROFILE_SCOPE("Renderer Draw");
		Quiet::Renderer2D::BeginScene(m_CameraController.GetCamera());
		Quiet::Renderer2D::DrawQuad({  0.5f, -0.5f }, { 0.5f, 0.75f }, { m_SquareColor1 });
		Quiet::Renderer2D::DrawQuad({ -1.0f,  0.0f }, { 0.8f, 0.8f  }, { m_SquareColor2 });
		Quiet::Renderer2D::DrawQuadRotated({  1.5f, -0.5f }, { 0.5f, 0.75f }, glm::radians(rotation), { m_SquareColor3 });
		Quiet::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 20.0f, 20.0f }, m_CheckerboadTex, 10.0f);
		Quiet::Renderer2D::DrawQuadRotated({ -2.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }, glm::radians(m_Rotation1), m_CheckerboadTex, 20.0f);
		Quiet::Renderer2D::EndScene();

		Quiet::Renderer2D::BeginScene(m_CameraController.GetCamera());
		for(float y = -5.0f; y < 5.0f; y += 0.5f)
		{
			for(float x = -5.0f; x < 5.0f; x += 0.5f)
			{
				glm::vec4 color = { (x + 5.0f) / 10.0f, 0.4f, (y + 5.0f) / 10.0f, 0.5f};
				Quiet::Renderer2D::DrawQuad({ x, y }, { 0.45f, 0.45f }, color);
			}
		}
		Quiet::Renderer2D::EndScene();
#endif

#if Particle_System

		// Particle Scene
		if (Quiet::Input::IsMouseButtonPressed(Quiet::Mouse::ButtonLeft))
		{
			auto [x, y] = Quiet::Input::GetMousePosition();
			auto width = Quiet::Application::Get().GetWindow().GetWidth();
			auto height = Quiet::Application::Get().GetWindow().GetHeight();

			auto bounds = m_CameraController.GetBounds();
			auto pos = m_CameraController.GetCamera().GetPosition();

			x = (x / width) * bounds.GetWidth() - bounds.GetWidth() * 0.5f;
			y = bounds.GetHeight() * 0.5f - (y / height) * bounds.GetHeight();

			m_Particle.Position = { x + pos.x, y + pos.y };

			for (int i = 0; i < 5; i++)
				m_ParticleSystem.Emit(m_Particle);
		}
		m_ParticleSystem.OnUpdate(deltaTime);
		m_ParticleSystem.OnRender(m_CameraController.GetCamera());
#endif

		// Game Scene
		Quiet::Renderer2D::BeginScene(m_CameraController.GetCamera());

		for (uint32_t y = 0; y < m_MapHeight; y++)
		{
			for (uint32_t x = 0; x < m_MapWidth; x++)
			{
				char tileType = s_MapTiles[x + y * m_MapWidth];
				Quiet::Ref<Quiet::SubTexture2D> texture;
				if (s_TextureMap.find(tileType) != s_TextureMap.end())
					texture = s_TextureMap[tileType];
				else
					texture = m_TextureStairs;

				Quiet::Renderer2D::DrawQuad({x - (m_MapWidth / 2.0f),y - (m_MapHeight / 2.0f),0.5f }, { 1.0f,1.0f }, texture);
			}
		}

		//Quiet::Renderer2D::DrawQuad({ 0.0f,0.0f,0.0f }, { 1.0f,1.0f }, m_TextureStairs);
		//Quiet::Renderer2D::DrawQuad({ 1.0f,0.0f,0.0f }, { 1.0f,1.0f }, m_TextureBarrel);
		//Quiet::Renderer2D::DrawQuad({ -1.0f,0.0f,0.0f }, { 1.0f,2.0f }, m_TextureTree);
		Quiet::Renderer2D::EndScene();

	}
}

void Sandbox2D::OnImGuiRender() {
	QUIET_PROFILE_FUNCTION();
	ImGui::Begin("Settings");
	{
		ImGui::Separator();
		ImGui::Text("COLORS");
		ImGui::SliderFloat("Rotation 1", &m_Rotation1, -360, 360);
		ImGui::SliderFloat("Rotation 2", &m_Rotation2, -360, 360);
		ImGui::ColorEdit4("Color 1", glm::value_ptr(m_SquareColor1));
		ImGui::ColorEdit4("Color 2", glm::value_ptr(m_SquareColor2));
		ImGui::ColorEdit4("Color 3", glm::value_ptr(m_SquareColor3));
		ImGui::Separator();
		ImGui::Text("Tiles");
		ImGui::Separator();
		ImGui::Text("Renderer 2D Stats");
		auto stats = Quiet::Renderer2D::GetStats();
		ImGui::Text("-Draw Calls: %d", stats.DrawCalls);
		ImGui::Text("-Quad Count: %d", stats.QuadCount);
		ImGui::Text("-Vertices: %d", stats.GetTotalVertexCount());
		ImGui::Text("-Indices: %d", stats.GetTotalIndexCount());
	}
	ImGui::End();
}

void Sandbox2D::OnEvent(Quiet::Event& event) {
	m_CameraController.OnEvent(event);
}
