#pragma once
// define this after the class headers

#if defined(_MSC_VER)
	#define GES_DEBUG_BREAK() __debugbreak()
#else
	#define GES_DEBUG_BREAK()
#endif

#if defined(_MSC_VER)
	#define FUNCTION_NAME __FUNCTION__
#else
	#define FUNCTION_NAME
#endif

#if defined(GES_FEATURE_LOGGER) && !defined(GES_SHIPPING)
	#define GES_LOGGER_ENABLED
#endif
#if defined(GES_LOGGER_ENABLED)
	// core logger
	#define GES_CORE_TRACE(...) GES::Log::GetCoreLogger()->trace(__VA_ARGS__)
	#define GES_CORE_INFO(...)  GES::Log::GetCoreLogger()->info(__VA_ARGS__)
	#define GES_CORE_WARN(...)  GES::Log::GetCoreLogger()->warn(__VA_ARGS__)
	#define GES_CORE_ERROR(...) GES::Log::GetCoreLogger()->error(__VA_ARGS__)
	#define GES_CORE_ASSERT(statement, ...)\
		if(statement) { /**/ } else { GES::Log::GetCoreLogger()->critical(__VA_ARGS__); GES_DEBUG_BREAK(); }

	// client logger
	#define GES_TRACE(...) GES::Log::GetClientLogger()->trace(__VA_ARGS__)
	#define GES_INFO(...)  GES::Log::GetClientLogger()->info(__VA_ARGS__)
	#define GES_WARN(...)  GES::Log::GetClientLogger()->warn(__VA_ARGS__)
	#define GES_ERROR(...) GES::Log::GetClientLogger()->error(__VA_ARGS__)
	#define GES_ASSERT(statement, ...)\
		if(statement) { /**/ } else { GES::Log::GetClientLogger()->critical(__VA_ARGS__); GES_DEBUG_BREAK(); }
#else
	// core logger
	#define GES_CORE_TRACE(...)
	#define GES_CORE_INFO(...)
	#define GES_CORE_WARN(...)
	#define GES_CORE_ERROR(...)
	#define GES_CORE_ASSERT(statement, ...)

	// client logger
	#define GES_TRACE(...)
	#define GES_INFO(...)
	#define GES_WARN(...)
	#define GES_ERROR(...)
	#define GES_ASSERT(statement, ...)
#endif

#if defined(GES_FEATURE_INSTRUMENTOR) && !defined(GES_SHIPPING)
	#define GES_INSTRUMENTOR_ENABLED
#endif
#if defined(GES_INSTRUMENTOR_ENABLED)
	#define GES_PROFILE_SET_ENABLED(value) GES::Instrumentor::SetEnabled(value)
	#define GES_PROFILE_GET_ENABLED() GES::Instrumentor::GetEnabled()
	#define GES_PROFILE_BEGIN_SESSION(name, filepath) GES::Instrumentor::Get().BeginSession(name, filepath)
	#define GES_PROFILE_END_SESSION() GES::Instrumentor::Get().EndSession()
	#define GES_PROFILE_SCOPE(name) GES::InstrumentationTimer GES_TOKENIZE_A_MACRO(timer, __LINE__)(name);
	#define GES_PROFILE_FUNCTION() GES_PROFILE_SCOPE(FUNCTION_NAME)
#else
	#define GES_PROFILE_SET_ENABLED(value)
	#define GES_PROFILE_GET_ENABLED() false
	#define GES_PROFILE_BEGIN_SESSION(name, filepath)
	#define GES_PROFILE_END_SESSION()
	#define GES_PROFILE_SCOPE(name)
	#define GES_PROFILE_FUNCTION()
#endif

// #define GES_PROFILE_SCOPE_OLD(name) GES::ScopedProfiler GES_TOKENIZE_A_MACRO(profiler, __LINE__)(name,\
// 	[&](ProfileResult profileResult) { m_ProfileResults.push_back(profileResult); }\
// )
