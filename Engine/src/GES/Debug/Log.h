#pragma once
#include "GES/Core/Code.h"

#define GES_FEATURE_LOGGER

#if !defined(GES_BYPASS_VENDOR_HEADERS)
	#include <spdlog/spdlog.h>
	#include <spdlog/fmt/ostr.h>
#endif

#if defined(GES_SHARED)
GES_EXTERN template class GES_DLL Ref<spdlog::logger>;
#endif

namespace GES {
	class GES_DLL Log
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
