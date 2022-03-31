#pragma once

#include "Core.h"

#include "Window.h"
#include "Quiet/LayerStack.h"
#include "Quiet/Events/Event.h"
#include "Quiet/Events/ApplicationEvent.h"

#include "Quiet/ImGui/ImGuiLayer.h"

#include "Quiet/Renderer/Shader.h"

namespace Quiet {
	
	class QUIET_API Application {
	public:
		Application();
		virtual ~Application();
		
		void Run();
		void OnEvent(Event& event);
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		inline Window& GetWindow() { return *m_Window; }
		inline static Application& Get() { return *s_Instance; }
		
	private:
		bool OnWindowClose(WindowCloseEvent& event);
		
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		LayerStack m_LayerStack;
		bool m_Running = true;

		unsigned int m_VertexArray;
		unsigned int m_VertexBuffer;
		unsigned int m_IndexBuffer;
		std::unique_ptr<Shader> m_Shader;

	private:
		static Application* s_Instance;
	};
	
	// To be defined in client
	Application* CreateApplication();
}

