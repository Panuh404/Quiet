#pragma once

#include "Quiet/Core/Core.h"

#include "Quiet/Core/Window.h"
#include "Quiet/Core/LayerStack.h"
#include "Quiet/Events/Event.h"
#include "Quiet/Events/ApplicationEvent.h"
#include "Quiet/Core/Timestep.h"

#include "Quiet/ImGui/ImGuiLayer.h"

#include "Quiet/Renderer/Shader.h"
#include "Quiet/Renderer/VertexArray.h"
#include "Quiet/Renderer/OrthographicCamera.h"

int main(int argc, char** argv);

namespace Quiet
{
	class Application
	{
	public:
		Application();
		virtual ~Application();
		
		void OnEvent(Event& event);
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		Window& GetWindow() { return *m_Window; }
		void Close();

		static Application& Get() { return *s_Instance; }
		
	private:
		Scope<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		LayerStack m_LayerStack;
		bool m_Running = true;
		bool m_Minimized = false;
		float m_LastFrameTime = 0.0f;
		
		static Application* s_Instance;
		friend int ::main(int argc, char** argv);

	private:
		void Run();
		bool OnWindowClose(WindowCloseEvent& event);
		bool OnWindowResize(WindowResizeEvent& event);
	};
	// To be defined in client
	Application* CreateApplication();
}