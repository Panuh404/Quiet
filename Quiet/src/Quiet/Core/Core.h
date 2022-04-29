#pragma once
#include <memory>

// Platform Detection using predefined macros (Windows)
#ifdef _WIN32
	// Windows
	#ifdef _WIN64
		// Windows 64-bit (x64)
		#define QUIET_PLATFORM_WINDOWS
	#else
		// Windows 32-bit (x86)
		#error "x86 Builds are not supported"
	#endif

// Platform Detection using predefined macros (Apple)
#elif defined(__APPLE__) || defined(__MACH__)
	#include <TargetConditionals.h>
	#if TARGET_IPHONE_SIMULATOR
		// iOS in Xcode
		#error "IOS Simulators are not supported"
	#elif TARGET_OS_IPHONE
		// iOS on iPhone
		#define QUIET_PLATFORM_IOS
	#elif TARGET_OS_MAC
		// iOS on Mac
		#define QUIET_PLATFORM_OSX
	#else
		#define QUIET_API __declspec(dllimport)
		#error "Unknown Apple platform"
	#endif

// Platform Detection using predefined macros (Android)
	/* We have to check Android before Linux,
	 * since android is base on the linux kernel
	 * it has __linux__ defined */
#elif defined(__ANDROID__)
	#define QUIET_PLATFORM_ANDROID
	#error "Android is not supported"

// Platform Detection using predefined macros (Linux)
#elif defined(__linux__)
	#define QUIET_PLATFORM_LINUX
	#error "Linux is not supported"

#else 
	#error "Unknown Platform!"
#endif
// End Platform Detection


// Dynamic Linking Support
#ifdef QUIET_PLATFORM_WINDOWS
	#if QUIET_DYNAMIC_LINK
		#ifdef QUIET_BUILD_DLL
			#define QUIET_API __declspec(dllexport)
		#else
			#define QUIET_API __declspec(dllinport)
		#endif
	#else
		#define QUIET_API
	#endif
#else
	#error "Quiet Currently only supports Windows!"
#endif


// Debug Settings
#ifdef QUIET_DEBUG
	#if defined(QUIET_PLATFORM_WINDOWS)
		#define QUIET_DEBUGBREAK() __debugbreak()
	#elif defined(QUIET_PLATFORM_LINUX)
		#define QUIET_DEBUGBREAK() raise(SIGTRAP)
	#else
		#error "Platform doesn't support debugbreak yet!"
	#endif
	#define QUIET_ENABLE_ASSERTS
#else
	#define QUIET_DEBUGBREAK()
#endif


#ifdef QUIET_ENABLE_ASSERTS
	#define QUIET_ASSERT(x, ...)		{ if(!(x)) { QUIET_ERROR("Assertion Failed: {0}", __VA_ARGS__); QUIET_DEBUGBREAK(); } }
	#define QUIET_CORE_ASSERT(x, ...)	{ if(!(x)) { QUIET_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); QUIET_DEBUGBREAK(); } }
#else
	#define QUIET_ASSERT(x, ...)
	#define QUIET_CORE_ASSERT(x, ...)
#endif

// Binds
#define BIT(x) (1 << x)
#define QUIET_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)


// Templates
namespace Quiet
{
	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		//Scope instead of raw pointers
		return std::make_unique<T>(std::forward<Args>(args)...); 
	}
	
	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		//Ref instead of raw pointers
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
}