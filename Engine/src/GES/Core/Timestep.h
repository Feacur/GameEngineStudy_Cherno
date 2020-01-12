#pragma once;

namespace GES
{
	class Timestep
	{
	public:
		Timestep(r32 seconds = 0.0f)
			: m_Seconds(seconds) {}

		operator r32() const { return m_Seconds; }

		r32 GetSeconds() const { return m_Seconds; }
		r32 GetMilliseconds() const { return m_Seconds * 1000.0f; }

	private:
		r32 m_Seconds;
	};
}
