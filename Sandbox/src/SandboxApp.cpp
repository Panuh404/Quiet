#include "Quiet.h"

class ExampleLayer : public Quiet::Layer {
public:
	ExampleLayer() : Layer("Example") {}
	
	void OnUpdate() override {
		//QT_INFO("ExampleLayer::Update");
	}
	
	void OnEvent(Quiet::Event& event) override {
		QT_TRACE("{0}", event);
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