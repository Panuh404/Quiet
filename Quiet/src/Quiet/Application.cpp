#include "Quiet_pch.h"
#include "Application.h"

#include "glad/glad.h"

#include "Input.h"

namespace Quiet {
	
	Application* Application::s_Instance = nullptr;

	Application::Application() {
		QUIET_ASSERT(!s_Instance, "Application already exist!");
		s_Instance = this;
		
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));


	}
	
	Application::~Application() {
		
	}

	void Application::PushLayer(Layer* layer) {
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}
	
	void Application::PushOverlay(Layer* overlay) {
		m_LayerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}
	
	void Application::OnEvent(Event& event) {
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<WindowCloseEvent>(std::bind(&Application::OnWindowClose, this, std::placeholders::_1));
		
		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();) {
			(*--it)->OnEvent(event);
			if (event.m_Handled) {
				break;
			}
		}
	}
	
	bool Application::OnWindowClose(WindowCloseEvent& event) {
		m_Running = false;
		return true;
	}
	
	void Application::Run() {
		while (m_Running) {
			glClearColor(0.3f, 0.2f, 0.8f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			
			for (Layer* layer : m_LayerStack) {
				layer->OnUpdate();
			}
			
			// INPUT TEST
			//auto [x, y] = Input::GetMousePosition();
			//QUIET_CORE_TRACE("{0}, {1}", x, y);
			
			m_Window->OnUpdate();
		}
	}
}
