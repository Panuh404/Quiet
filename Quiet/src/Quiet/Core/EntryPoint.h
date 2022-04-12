#pragma once
#include "Quiet/Core/Core.h"

#ifdef QUIET_PLATFORM_WINDOWS

extern Quiet::Application* Quiet::CreateApplication();

int main(int argc, char** argv) {
	
	Quiet::Log::Init();
	
	QUIET_PROFILE_BEGIN_SESSION("Startup", "QuietProfile-Startup.json");
	auto app = Quiet::CreateApplication();
	QUIET_PROFILE_END_SESSION();
	
	QUIET_PROFILE_BEGIN_SESSION("Runtime", "QuietProfile-Runtime.json");
	app->Run();
	QUIET_PROFILE_END_SESSION();
	
	QUIET_PROFILE_BEGIN_SESSION("Shutdown", "QuietProfile-Shutdown.json");
	delete app;
	QUIET_PROFILE_END_SESSION();
}

#endif