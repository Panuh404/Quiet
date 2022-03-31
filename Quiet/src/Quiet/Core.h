#pragma once

#ifdef QUIET_PLATFORM_WINDOWS
	#if QUIET_DYNAMIC_LINK
		#ifdef QUIET_BUILD_DLL
			#define QUIET_API __declspec(dllexport)
		#else
			#define QUIET_API __declspec(dllimport)
		#endif
	#else
		#define QUIET_API	
	#endif
#else
	#error Quiet only supports Windows!
#endif


#ifdef QUIET_DEBUG
	#define QUIET_ENABLE_ASSERTS
#endif


#ifdef QUIET_ENABLE_ASSERTS
	#define QUIET_ASSERT(x, ...)		{ if(!(x)) { QUIET_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define QUIET_CORE_ASSERT(x, ...)	{ if(!(x)) { QUIET_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define QUIET_ASSERT(x, ...)
	#define QUIET_CORE_ASSERT(x, ...)
#endif


#define BIT(x) (1 << x)


#define QUIET_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)