#pragma once

#ifdef QT_PLATFORM_WINDOWS

extern Quiet::Application* Quiet::CreateApplication();

int main(int argc, char** argv) {
	
	Quiet::Log::Init();
	QT_CORE_WARN("Initialized Log!");
	QT_CLIENT_INFO("Welcome!");
	
	auto app = Quiet::CreateApplication();
	app->Run();
	delete app;
}

#endif