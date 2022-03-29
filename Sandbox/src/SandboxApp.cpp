#include "Quiet.h"

class ExampleLayer : public Quiet::Layer {
public:
	ExampleLayer() : Layer("Example") {}
	
	void OnUpdate() override {
		if (Quiet::Input::IsKeyPressed(Quiet::Key::Tab)) {
			QUIET_TRACE("Tab Key Pressed");
		}
	}
	
	void OnEvent(Quiet::Event& event) override {
		if (event.GetEventType() == Quiet::EventType::KeyPressed) {
			Quiet::KeyPressedEvent& e = (Quiet::KeyPressedEvent&)event;
			QUIET_TRACE("{0}", (char)e.GetKeyCode());
		}
	}
};

class Sandbox : public Quiet::Application {
public:
	Sandbox() {
		PushLayer(new ExampleLayer());
	}
	
	~Sandbox() {

	}
};

Quiet::Application* Quiet::CreateApplication() {
	return new Sandbox();
}