#pragma once

#include "Core.h"

#include "Window.h"
#include "Quiet/LayerStack.h"
#include "Quiet/Events/Event.h"
#include "Quiet/Events/ApplicationEvent.h"

#include "Quiet/ImGui/ImGuiLayer.h"

#include "Quiet/Renderer/Shader.h"
#include "Quiet/Renderer/VertexArray.h"

namespace Quiet {
	
	class Application {
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
		
		std::shared_ptr<Shader> m_Shader;
		std::shared_ptr<VertexArray> m_TriangleVA;
		
		std::shared_ptr<Shader> m_BlueShader;
		std::shared_ptr<VertexArray> m_SquareVA;

	private:
		static Application* s_Instance;
	};
	
	// To be defined in client
	Application* CreateApplication();
}

