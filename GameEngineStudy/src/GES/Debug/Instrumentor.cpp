#include "ges_pch.h"
#include "Instrumentor.h"

namespace GES
{
	struct ProfileResult
	{
		std::string Name;
		int64 Start, End;
		size_t ThreadID;
	};

	struct InstrumentationSession
	{
		std::string Name;
		std::ofstream OutputStream;
	};

	Instrumentor::Instrumentor()
		: m_CurrentSession(nullptr), m_ProfileCount(0)
	{
	}

	void Instrumentor::BeginSession(cstring name, cstring filepath)
	{
		m_CurrentSession = new InstrumentationSession();
		m_CurrentSession->Name = name;
		
		m_CurrentSession->OutputStream.open(filepath);
		m_CurrentSession->OutputStream << "{\"otherData\": {},\"traceEvents\":[";
		m_CurrentSession->OutputStream.flush();
	}

	void Instrumentor::EndSession()
	{
		m_CurrentSession->OutputStream << "]}";
		m_CurrentSession->OutputStream.flush();
		m_CurrentSession->OutputStream.close();

		delete m_CurrentSession;
		m_CurrentSession = nullptr;
		
		m_ProfileCount = 0;
	}

	void Instrumentor::WriteProfile(ProfileResult const & result)
	{
		if (m_ProfileCount++ > 0)
			m_CurrentSession->OutputStream << ",";

		std::string name = result.Name;
		std::replace(name.begin(), name.end(), '"', '\'');

		m_CurrentSession->OutputStream << "{";
		m_CurrentSession->OutputStream << "\"cat\":\"function\",";
		m_CurrentSession->OutputStream << "\"dur\":" << (result.End - result.Start) << ',';
		m_CurrentSession->OutputStream << "\"name\":\"" << name << "\",";
		m_CurrentSession->OutputStream << "\"ph\":\"X\",";
		m_CurrentSession->OutputStream << "\"pid\":0,";
		m_CurrentSession->OutputStream << "\"tid\":" << result.ThreadID << ",";
		m_CurrentSession->OutputStream << "\"ts\":" << result.Start;
		m_CurrentSession->OutputStream << "}";

		m_CurrentSession->OutputStream.flush();
	}

	InstrumentationTimer::InstrumentationTimer(cstring name)
		: m_Name(name), m_Stopped(false)
	{
		m_StartTimepoint = std::chrono::high_resolution_clock::now();
	}

	InstrumentationTimer::~InstrumentationTimer()
	{
		if (!m_Stopped)
			Stop();
	}

	void InstrumentationTimer::Stop()
	{
		auto endTimepoint = std::chrono::high_resolution_clock::now();

		int64 start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch().count();
		int64 end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();

		size_t threadID = std::hash<std::thread::id>{}(std::this_thread::get_id());
		Instrumentor::Get().WriteProfile({ m_Name, start, end, threadID });

		m_Stopped = true;
	}
}
