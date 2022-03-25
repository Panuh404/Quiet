#include "Quiet.h"

class Sandbox : public Quiet::Application {
public:
	Sandbox() {
		
	}
	
	~Sandbox() {

	}
};

Quiet::Application* Quiet::CreateApplication() {

	return new Sandbox();
	
}