#pragma once
#include "GES/Core/Code.h"

#define FEATURE_GES_INSTRUMENTOR

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

		static bool GetEnabled() { return m_Enabled; }
		static void SetEnabled(bool value) { m_Enabled = value; }
		void WriteProfile(ProfileResult const & result);

	private:
		static bool m_Enabled;
		InstrumentationSession * m_CurrentSession;
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
		int64 m_StartNanoseconds;
	};
}
