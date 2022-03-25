#pragma once

#ifdef QUIET_PLATFORM_WINDOWS
	#ifdef QUIET_BUILD_DLL
		#define QUIET_API __declspec(dllexport)
	#else
		#define QUIET_API __declspec(dllimport)
	#endif
#else
	#error Quiet only supports Windows!
#endif

#ifdef QT_ENABLE_ASSERTS
	#define QT_ASSERT(x, ...) { if(!(x)) { QT_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define QT_CORE_ASSERT(x, ...) { if(!(x)) { QT_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define QT_ASSERT(x, ...)
	#define QT_CORE_ASSERT(x, ...)
#endif


#define BIT(x) (1 << x)