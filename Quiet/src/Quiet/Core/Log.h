#pragma once

#include "Core.h"

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

namespace Quiet
{
	class Log
	{
	public:
		static void Init();
		inline static Ref<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static Ref<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
		
	private:
		static Ref<spdlog::logger> s_CoreLogger;
		static Ref<spdlog::logger> s_ClientLogger;
	};
}

// CORE LOG MACROS
#define QUIET_CORE_ERROR(...)	::Quiet::Log::GetCoreLogger()->error(__VA_ARGS__)
#define QUIET_CORE_WARN(...)	::Quiet::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define QUIET_CORE_INFO(...)	::Quiet::Log::GetCoreLogger()->info(__VA_ARGS__)
#define QUIET_CORE_TRACE(...)	::Quiet::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define QUIET_CORE_CRITICAL(...)::Quiet::Log::GetCoreLogger()->critical(__VA_ARGS__)
								   
// CLIENT LOG MACROS			   
#define QUIET_ERROR(...)		::Quiet::Log::GetClientLogger()->error(__VA_ARGS__)
#define QUIET_WARN(...)			::Quiet::Log::GetClientLogger()->warn(__VA_ARGS__)
#define QUIET_INFO(...)			::Quiet::Log::GetClientLogger()->info(__VA_ARGS__)
#define QUIET_TRACE(...)		::Quiet::Log::GetClientLogger()->trace(__VA_ARGS__)
#define QUIET_CRITICAL(...)		::Quiet::Log::GetClientLogger()->critical(__VA_ARGS__)


