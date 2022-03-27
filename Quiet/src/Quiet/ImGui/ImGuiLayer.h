#pragma once

#include "Quiet/Layer.h"

#include "Quiet/Events/MouseEvent.h"
#include "Quiet/Events/KeyEvent.h"
#include "Quiet/Events/ApplicationEvent.h"

namespace Quiet {
	
	class QUIET_API ImGuiLayer : public Layer {
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach();
		void OnDetach();
		void OnUpdate();
		void OnEvent(Event& event);
	private:
		float m_Time = 0.0f;
		
	private:
		bool OnMouseButtonPressedEvent	(MouseButtonPressedEvent& event);
		bool OnMouseButtonReleasedEvent	(MouseButtonReleasedEvent& event);
		bool OnMouseMovedEvent			(MouseMovedEvent& event);
		bool OnMouseScrolledEvent		(MouseScrolledEvent& event);
		bool OnKeyPressedEvent			(KeyPressedEvent& event);
		bool OnKeyReleasedEvent			(KeyReleasedEvent& event);
		bool OnKeyTypedEvent			(KeyTypedEvent& event);
		bool OnWindowResizeEvent		(WindowResizeEvent& event);
	};
}