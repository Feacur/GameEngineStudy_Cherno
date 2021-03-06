#pragma once
#include "GES/Core/Code.h"

#define GES_FEATURE_SCOPED_PROFILER

#if defined(GES_BYPASS_VENDOR_HEADERS)
	#include <chrono>
#endif

namespace GES
{
	template<typename Fn>
	class ScopedProfiler
	{
	public:
		ScopedProfiler(cstring name, Fn && func)
			: m_Name(name), m_Func(func), m_Stopped(false)
		{
			m_StartTimepoint = std::chrono::high_resolution_clock::now();
		}

		~ScopedProfiler()
		{
			if (!m_Stopped)
				Stop();
		}

		void Stop()
		{
			auto endTimepoint = std::chrono::high_resolution_clock::now();

			s64 start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch().count();
			s64 end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();

			m_Stopped = true;

			r32 duration = (end - start) * 0.001f;
			m_Func({ m_Name, duration });
		}

	private:
		cstring m_Name;
		Fn m_Func;
		std::chrono::time_point<std::chrono::steady_clock> m_StartTimepoint;
		bool m_Stopped;
	};
}
