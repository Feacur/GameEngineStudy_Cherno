#pragma once
// define this after the class headers

#if defined(GES_LOGGER) && !defined(SHIPPING)
	#define GES_LOGGER_ENABLED
#endif
#if defined(GES_LOGGER_ENABLED)
	// core logger
	#define GES_CORE_TRACE(...)    GES::Log::GetCoreLogger()->trace(__VA_ARGS__)
	#define GES_CORE_INFO(...)     GES::Log::GetCoreLogger()->info(__VA_ARGS__)
	#define GES_CORE_WARN(...)     GES::Log::GetCoreLogger()->warn(__VA_ARGS__)
	#define GES_CORE_ERROR(...)    GES::Log::GetCoreLogger()->error(__VA_ARGS__)
	#define GES_CORE_CRITICAL(...) GES::Log::GetCoreLogger()->critical(__VA_ARGS__)
	#define GES_CORE_ASSERT(x, ...) { if(x) { /**/ } else { GES_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); CODE_BREAK(); } }

	// client logger
	#define GES_TRACE(...)    GES::Log::GetClientLogger()->trace(__VA_ARGS__)
	#define GES_INFO(...)     GES::Log::GetClientLogger()->info(__VA_ARGS__)
	#define GES_WARN(...)     GES::Log::GetClientLogger()->warn(__VA_ARGS__)
	#define GES_ERROR(...)    GES::Log::GetClientLogger()->error(__VA_ARGS__)
	#define GES_CRITICAL(...) GES::Log::GetClientLogger()->critical(__VA_ARGS__)
	#define GES_ASSERT(x, ...) { if(x) { /**/ } else { GES_ERROR("Assertion Failed: {0}", __VA_ARGS__); CODE_BREAK(); } }
#else
	// core logger
	#define GES_CORE_TRACE(...)
	#define GES_CORE_INFO(...)
	#define GES_CORE_WARN(...)
	#define GES_CORE_ERROR(...)
	#define GES_CORE_CRITICAL(...)
	#define GES_CORE_ASSERT(x, ...)

	// client logger
	#define GES_TRACE(...)
	#define GES_INFO(...)
	#define GES_WARN(...)
	#define GES_ERROR(...)
	#define GES_CRITICAL(...)
	#define GES_ASSERT(x, ...)
#endif

#if defined(GES_INSTRUMENTOR) && !defined(SHIPPING)
	#define GES_INSTRUMENTOR_ENABLED
#endif
#if defined(GES_INSTRUMENTOR_ENABLED)
	#define GES_PROFILE_SET_ENABLED(value) GES::Instrumentor::SetEnabled(value)
	#define GES_PROFILE_GET_ENABLED() GES::Instrumentor::GetEnabled()
	#define GES_PROFILE_BEGIN_SESSION(name, filepath) GES::Instrumentor::Get().BeginSession(name, filepath)
	#define GES_PROFILE_END_SESSION() GES::Instrumentor::Get().EndSession()
	#define GES_PROFILE_SCOPE(name) GES::InstrumentationTimer TOKENIZE_A_MACRO(timer, __LINE__)(name);
	#define GES_PROFILE_FUNCTION() GES_PROFILE_SCOPE(FUNCTION_NAME)
#else
	#define GES_PROFILE_SET_ENABLED(value)
	#define GES_PROFILE_GET_ENABLED() false
	#define GES_PROFILE_BEGIN_SESSION(name, filepath)
	#define GES_PROFILE_END_SESSION()
	#define GES_PROFILE_SCOPE(name)
	#define GES_PROFILE_FUNCTION()
#endif

// #define GES_PROFILE_SCOPE_OLD(name) GES::ScopedProfiler TOKENIZE_A_MACRO(profiler, __LINE__)(name,\
// 	[&](ProfileResult profileResult) { m_ProfileResults.push_back(profileResult); }\
// )
