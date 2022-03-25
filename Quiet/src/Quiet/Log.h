#pragma once
#include <memory>

#include "Core.h"
#include "spdlog/spdlog.h"

namespace Quiet {
	
	class QUIET_API Log
	{
	public:
		static void Init();
		
		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
		
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

// Core log macros
#define QT_CORE_ERROR(...)		::Quiet::Log::GetCoreLogger()->error(__VA_ARGS__)
#define QT_CORE_WARN(...)		::Quiet::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define QT_CORE_INFO(...)		::Quiet::Log::GetCoreLogger()->info(__VA_ARGS__)
#define QT_CORE_TRACE(...)		::Quiet::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define QT_CORE_FATAL(...)		::Quiet::Log::GetCoreLogger()->fatal(__VA_ARGS__)
								   
// Client log macros			   
#define QT_CLIENT_ERROR(...)	::Quiet::Log::GetClientLogger()->error(__VA_ARGS__)
#define QT_CLIENT_WARN(...)		::Quiet::Log::GetClientLogger()->warn(__VA_ARGS__)
#define QT_CLIENT_INFO(...)		::Quiet::Log::GetClientLogger()->info(__VA_ARGS__)
#define QT_CLIENT_TRACE(...)	::Quiet::Log::GetClientLogger()->trace(__VA_ARGS__)
#define QT_CLIENT_FATAL(...)	::Quiet::Log::GetClientLogger()->fatal(__VA_ARGS__)


