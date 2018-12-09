#pragma once

#include "Core.h"
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

GES_TEMPLATE template class GES_API std::shared_ptr<spdlog::logger>;

namespace GES {
	class GES_API Log
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

// core logger
#define GES_CORE_TRACE(...) GES::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define GES_CORE_INFO(...)  GES::Log::GetCoreLogger()->info(__VA_ARGS__)
#define GES_CORE_WARN(...)  GES::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define GES_CORE_ERROR(...) GES::Log::GetCoreLogger()->error(__VA_ARGS__)
#define GES_CORE_FATAL(...) GES::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// client logger
#define GES_TRACE(...) GES::Log::GetClientLogger()->trace(__VA_ARGS__)
#define GES_INFO(...)  GES::Log::GetClientLogger()->info(__VA_ARGS__)
#define GES_WARN(...)  GES::Log::GetClientLogger()->warn(__VA_ARGS__)
#define GES_ERROR(...) GES::Log::GetClientLogger()->error(__VA_ARGS__)
#define GES_FATAL(...) GES::Log::GetClientLogger()->fatal(__VA_ARGS__)
