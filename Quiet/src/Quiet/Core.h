#pragma once

#ifdef QT_PLATFORM_WINDOWS
	#ifdef QT_BUILD_DLL
		#define QUIET_API __declspec(dllexport)
	#else
		#define QUIET_API __declspec(dllimport)
	#endif
#else
	#error Quiet only supports Windows!
#endif
