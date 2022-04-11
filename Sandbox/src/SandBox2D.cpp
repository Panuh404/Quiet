#include "Sandbox2D.h"

#include <ImGui/imgui.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <chrono>

template<typename Fn>
class Timer {
public:
	Timer(const char* name, Fn&& function) : 
		m_Name(name), m_Stopped(false), m_Function(function)
	{
		m_StartTimepoint = std::chrono::high_resolution_clock::now();
	}
	
	~Timer() {
		if (!m_Stopped) {
			Stop();
		}
	}
	
	void Stop() {
		auto endTimepoint = std::chrono::high_resolution_clock::now();
		
		long long start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch().count();
		long long end =   std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();

		m_Stopped = true;
		
		float duration = (end - start) * 0.001f;
		//std::cout << m_Name << ": " << duration << " ms" << std::endl;
		m_Function({ m_Name, duration });
	}
private:
	const char* m_Name;
	std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTimepoint;
	bool m_Stopped;
	Fn m_Function;
};

#define QUIET_PROFILE_SCOPE(name) Timer timer##__LINE__(name, [&](ProfileResult profileResult) { m_ProfileResults.push_back(profileResult); });

Sandbox2D::Sandbox2D() : Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f) {	
}

void Sandbox2D::OnAttach() {
	m_Texture = Quiet::Texture2D::Create("res/textures/Checkerboard.png");
}

void Sandbox2D::OnDetach() {
	
}

void Sandbox2D::OnUpdate(Quiet::Timestep deltaTime) {

	QUIET_PROFILE_SCOPE("Sandbox2D::OnUpdate");
	// Update
	{
		QUIET_PROFILE_SCOPE("CameraController::OnUpdate");
		m_CameraController.OnUpdate(deltaTime);
	}

	// Render
	{
		QUIET_PROFILE_SCOPE("Renderer Pref");
		Quiet::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Quiet::RenderCommand::Clear();
	}
	// Draw
	{
		QUIET_PROFILE_SCOPE("Renderer Draw");
		Quiet::Renderer2D::BeginScene(m_CameraController.GetCamera());
		Quiet::Renderer2D::DrawQuad({  0.5f, -0.5f }, { 0.5f, 0.75f }, { m_SquareColor1 });
		Quiet::Renderer2D::DrawQuad({ -1.0f,  0.0f }, { 0.8f, 0.8f  }, { m_SquareColor2 });
		Quiet::Renderer2D::DrawQuad({  0.0f,  0.0f, -0.1f }, { 5.0f, 5.0f }, m_Texture);
		Quiet::Renderer2D::EndScene();
	}

}

void Sandbox2D::OnImGuiRender() {
	ImGui::Begin("Settings");
	ImGui::Text("COLORS");
	ImGui::ColorEdit4("Color 1", glm::value_ptr(m_SquareColor1));
	ImGui::ColorEdit4("Color 2", glm::value_ptr(m_SquareColor2));

	ImGui::Text("PROFILER");
	for (auto& result : m_ProfileResults) {
		char label[50];
		strcpy(label, "%.3f ms ");
		strcat(label, result.Name);
		ImGui::Text(label, result.Time);
	}
	m_ProfileResults.clear();

	ImGui::End();
}

void Sandbox2D::OnEvent(Quiet::Event& event) {
	m_CameraController.OnEvent(event);
}
