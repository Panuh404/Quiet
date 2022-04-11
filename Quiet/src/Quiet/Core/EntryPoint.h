#pragma once
#include "Quiet/Core/Core.h"

#ifdef QUIET_PLATFORM_WINDOWS

extern Quiet::Application* Quiet::CreateApplication();

int main(int argc, char** argv) {
	
	Quiet::Log::Init();
	QUIET_CORE_WARN("Initialized Log!");
	QUIET_INFO("Welcome!");
	
	auto app = Quiet::CreateApplication();
	app->Run();
	delete app;
}

#endif