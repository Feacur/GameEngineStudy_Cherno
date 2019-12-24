#pragma once
#include "GES/Core/Code.h"

#if defined(GES_BYPASS_VENDOR_HEADERS)
	#include <chrono>
	#include <algorithm>
	#include <thread>
#endif

namespace GES {
	struct InstrumentationSession;
	struct ProfileResult;

	class Instrumentor
	{
	public:
		Instrumentor();

	public:
		static Instrumentor & Get()
		{
			static Instrumentor instance;
			return instance;
		}

	public:
		void BeginSession(cstring name, cstring filepath);
		void EndSession();

		void WriteProfile(ProfileResult const & result);

	private:
		InstrumentationSession * m_CurrentSession;
		int32 m_ProfileCount;
	};

	class InstrumentationTimer
	{
	public:
		InstrumentationTimer(cstring name);
		~InstrumentationTimer();

	private:
		void Stop();

	private:
		cstring m_Name;
		std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTimepoint;
		bool m_Stopped;
	};
}

#define GES_PROFILE
#if defined(GES_PROFILE)
	#define GES_PROFILE_BEGIN_SESSION(name, filepath) ::GES::Instrumentor::Get().BeginSession(name, filepath)
	#define GES_PROFILE_END_SESSION() ::GES::Instrumentor::Get().EndSession()
	#define GES_PROFILE_SCOPE(name) ::GES::InstrumentationTimer TOKENIZE_A_MACRO(timer, __LINE__)(name);
	#define GES_PROFILE_FUNCTION() GES_PROFILE_SCOPE(__FUNCSIG__)
#else
	#define GES_PROFILE_BEGIN_SESSION(name, filepath)
	#define GES_PROFILE_END_SESSION()
	#define GES_PROFILE_SCOPE(name)
	#define GES_PROFILE_FUNCTION()
#endif
