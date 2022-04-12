#pragma once

#include "Quiet/Core/Layer.h"

#include "Quiet/Events/MouseEvent.h"
#include "Quiet/Events/KeyEvent.h"
#include "Quiet/Events/ApplicationEvent.h"

namespace Quiet
{
	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		
		void Begin();
		void End();

	private:
		float m_Time = 0.0f;
	};
}