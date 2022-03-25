#include "Quiet_pch.h"
#include "Application.h"

#include "Quiet/Events/ApplicationEvent.h"
#include "Quiet/Log.h"

namespace Quiet {
	
	Application::Application() {
		m_Window = std::unique_ptr<Window>(Window::Create());
	}
	
	Application::~Application() {
		
	}
	
	void Application::Run() {
		while (m_Running) {
			m_Window->OnUpdate();
		}
	}
}
