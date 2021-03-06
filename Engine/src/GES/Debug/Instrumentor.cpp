#include "ges_pch.h"
#include "Instrumentor.h"

namespace GES
{
	struct ProfileResult
	{
		std::string Name;
		s64 Start, End;
		size_t ThreadID;
	};

	struct InstrumentationSession
	{
		cstring Name;
		s32 ProfileCount;
		std::ofstream OutputStream;
	};

	bool Instrumentor::m_Enabled = false;

	Instrumentor::Instrumentor()
		: m_CurrentSession(nullptr)
	{
	}

	void Instrumentor::BeginSession(cstring name, cstring filepath)
	{
		m_CurrentSession = new InstrumentationSession();
		m_CurrentSession->Name = name;
		m_CurrentSession->ProfileCount = 0;
		
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
	}

	void Instrumentor::WriteProfile(ProfileResult const & result)
	{
		if (m_CurrentSession == nullptr) { return; }
		if (!m_Enabled) { return; }

		if (m_CurrentSession->ProfileCount++ > 0)
			m_CurrentSession->OutputStream << ",";

		std::string name = result.Name;
		std::replace(name.begin(), name.end(), '"', '\'');
		std::replace(name.begin(), name.end(), '\\', '/');

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
		: m_Name(name)
	{
		auto time = std::chrono::high_resolution_clock::now();
		// time = std::chrono::time_point_cast<std::chrono::nanoseconds>(time);
		m_StartNanoseconds = time.time_since_epoch().count();
	}

	InstrumentationTimer::~InstrumentationTimer()
	{
		Stop();
	}

	void InstrumentationTimer::Stop()
	{
		auto time = std::chrono::high_resolution_clock::now();
		// time = std::chrono::time_point_cast<std::chrono::nanoseconds>(time);
		s64 endNanoseconds = time.time_since_epoch().count();

		size_t threadID = std::hash<std::thread::id>{}(std::this_thread::get_id());
		Instrumentor::Get().WriteProfile({ m_Name, m_StartNanoseconds, endNanoseconds, threadID });
	}
}
