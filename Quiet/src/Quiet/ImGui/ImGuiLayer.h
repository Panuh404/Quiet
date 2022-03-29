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
	};
}