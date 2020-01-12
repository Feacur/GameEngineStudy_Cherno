#pragma once
#include "GES.h"

namespace FloatyRocket
{
	class ParticleSystem;

	class Player
	{
	public:
		void Reset();
		void OnUpdate(GES::Timestep ts, ParticleSystem & particleSystem);
		void OnRender(GES::Ref<GES::Texture2D> texture);

	public:
		glm::vec2 GetPosition() { return m_Position; }
		r32 GetRotation() { return glm::radians(m_Velocity.y * 4.0f - 90.0f); }

	private:
		glm::vec2 m_Position;
		glm::vec2 m_Velocity;

		r32 m_ParticleFirePeriod = 0.1f;
		r32 m_ParticleFireElapsed;
		
		r32 m_ParticleSmokePeriod = 0.4f;
		r32 m_ParticleSmokeElapsed;
	};
}
