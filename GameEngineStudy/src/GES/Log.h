#pragma once

#include "Core.h"
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

#if defined(GES_SHARED)
GES_TEMPLATE template class GES_API Ref<spdlog::logger>;
#endif

namespace GES {
	class GES_API Log
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

#if !defined(SHIPPING)
	// core logger
	#define GES_CORE_TRACE(...)    GES::Log::GetCoreLogger()->trace(__VA_ARGS__)
	#define GES_CORE_INFO(...)     GES::Log::GetCoreLogger()->info(__VA_ARGS__)
	#define GES_CORE_WARN(...)     GES::Log::GetCoreLogger()->warn(__VA_ARGS__)
	#define GES_CORE_ERROR(...)    GES::Log::GetCoreLogger()->error(__VA_ARGS__)
	#define GES_CORE_CRITICAL(...) GES::Log::GetCoreLogger()->critical(__VA_ARGS__)

	// client logger
	#define GES_TRACE(...)    GES::Log::GetClientLogger()->trace(__VA_ARGS__)
	#define GES_INFO(...)     GES::Log::GetClientLogger()->info(__VA_ARGS__)
	#define GES_WARN(...)     GES::Log::GetClientLogger()->warn(__VA_ARGS__)
	#define GES_ERROR(...)    GES::Log::GetClientLogger()->error(__VA_ARGS__)
	#define GES_CRITICAL(...) GES::Log::GetClientLogger()->critical(__VA_ARGS__)
#else
	// core logger
	#define GES_CORE_TRACE(...)
	#define GES_CORE_INFO(...)
	#define GES_CORE_WARN(...)
	#define GES_CORE_ERROR(...)
	#define GES_CORE_CRITICAL(...)

	// client logger
	#define GES_TRACE(...)
	#define GES_INFO(...)
	#define GES_WARN(...)
	#define GES_ERROR(...)
	#define GES_CRITICAL(...)
#endif