#include "Quiet.h"
#include "Quiet/Core/EntryPoint.h"

#include <ImGui/imgui.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//#include "ExampleLayer.h"
#include "SandBox2D.h"

class Sandbox : public Quiet::Application
{
public:
	Sandbox()
	{
		//PushLayer(new ExampleLayer());
		PushLayer(new Sandbox2D());
	}
	~Sandbox() {}
};

Quiet::Application* Quiet::CreateApplication()
{
	return new Sandbox();
}