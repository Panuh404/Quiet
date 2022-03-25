#pragma once

#ifdef QT_PLATFORM_WINDOWS

extern Quiet::Application* Quiet::CreateApplication();

int main(int argc, char** argv) {
	auto app = Quiet::CreateApplication();
	app->Run();
	delete app;
}

#endif