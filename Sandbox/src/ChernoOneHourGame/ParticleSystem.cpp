#include "ParticleSystem.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/compatibility.hpp>

// @Note: probably I should factor out a new submodule
//        instead of copy-pasting chunks around...
// https://github.com/Feacur/CustomEngineStudy/blob/master/code/shared/random.h
inline static float hash_radius01(uint32 * state) {
	union { uint32 x; float xf; };  // local unionized values
	x = (*state = *state * 16807U); // hash
	x = (x >> 9) | 0x40000000U;     // clamp to [1 .. 2) * (2^1)
	return xf - 3;                  // return [2 .. 4) - 3
}

#define random_radius01() hash_radius01(&m_Random)
ParticleSystem::ParticleSystem()
{
	m_ParticlePool.resize(1000);
}

void ParticleSystem::Emit(const ParticleProps& particleProps)
{
	Particle& particle = m_ParticlePool[m_PoolIndex];
	particle.Active = true;
	particle.Position = particleProps.Position;
	particle.Rotation = random_radius01() * 2.0f * glm::pi<float>();

	// Velocity
	particle.Velocity = particleProps.Velocity;
	particle.Velocity.x += particleProps.VelocityVariation.x * random_radius01();
	particle.Velocity.y += particleProps.VelocityVariation.y * random_radius01();

	// Color
	particle.ColorBegin = particleProps.ColorBegin;
	particle.ColorEnd = particleProps.ColorEnd;

	// Size
	particle.SizeBegin = particleProps.SizeBegin + particleProps.SizeVariation * random_radius01();
	particle.SizeEnd = particleProps.SizeEnd;

	// Life
	particle.LifeTime = particleProps.LifeTime;
	particle.LifeRemaining = particleProps.LifeTime;

	m_PoolIndex = --m_PoolIndex % m_ParticlePool.size();
}

void ParticleSystem::OnUpdate(GES::Timestep ts)
{
	for (auto& particle : m_ParticlePool)
	{
		if (!particle.Active)
			continue;

		if (particle.LifeRemaining <= 0.0f)
		{
			particle.Active = false;
			continue;
		}

		particle.LifeRemaining -= ts;
		particle.Position += particle.Velocity * (float)ts;
		particle.Rotation += 0.01f * ts;
	}
}

void ParticleSystem::OnRender()
{
	for (auto& particle : m_ParticlePool)
	{
		if (!particle.Active)
			continue;

		float life = particle.LifeRemaining / particle.LifeTime;
		glm::vec4 color = glm::lerp(particle.ColorEnd, particle.ColorBegin, life);
		color.a = color.a * life;

		float size = glm::lerp(particle.SizeEnd, particle.SizeBegin, life);
		GES::Renderer2D::DrawQuad(particle.Position, { size, size }, particle.Rotation, color);
	}
}
