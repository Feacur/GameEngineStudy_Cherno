#include "ParticleSystem.h"

#include "ParticleProps.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/compatibility.hpp>

// @Note: probably I should factor out a new submodule
//        instead of copy-pasting chunks around...
// https://github.com/Feacur/CustomEngineStudy/blob/master/code/shared/random.h
inline static float hash_radius01(uint32 * state) {
	union { uint32 x; float xf; }; // local unionized values
	x = (*state = *state * 16807); // hash
	x = (x >> 9) | 0x40000000;     // clamp to [1 .. 2) * (2^1)
	return xf - 3;                 // return [2 .. 4) - 3
}

namespace FloatyRocket
{
	#define random_radius01() hash_radius01(&m_Random)
	ParticleSystem::ParticleSystem(int32 limit)
	{
		GES_PROFILE_FUNCTION();
		m_Index = 0;
		m_Limit = limit;
		m_Active.resize(limit);
		m_Lifetime.resize(limit);
		m_State.resize(limit);
		m_Motion.resize(limit);
		m_Rendering.resize(limit);
	}

	ParticleSystem::~ParticleSystem() = default;
	
	void ParticleSystem::Emit(ParticleProps const & props)
	{
		GES_PROFILE_FUNCTION();
		int32 index = m_Index;
		m_Index = (m_Index + 1) % m_Limit;

		m_Active[index] = true;

		ParticleLifetime & lifetime = m_Lifetime[index];
		lifetime.Duration = props.LifeTime;
		lifetime.Elapsed = 0;

		ParticleState & state = m_State[index];
		state.Position = props.Position;
		state.Rotation = props.Rotation + props.RotationVariation * random_radius01();

		ParticleMotion & motion = m_Motion[index];
		motion.Velocity = props.Velocity;
		motion.Velocity.x += props.VelocityVariation.x * random_radius01();
		motion.Velocity.y += props.VelocityVariation.y * random_radius01();

		motion.RotationSpeed = props.RotationSpeed + props.RotationSpeedVariation * random_radius01();

		ParticleRendering & rendering = m_Rendering[index];
		rendering.Color1 = props.Color1;
		rendering.Color2 = props.Color2;

		rendering.Size1 = props.Size1 + props.Size1Variation * random_radius01();
		rendering.Size2 = props.Size2;
	}

	void ParticleSystem::OnUpdate(GES::Timestep ts)
	{
		GES_PROFILE_FUNCTION();

		int32 limit = m_Limit;
		for (int32 i = 0; i < limit; i++)
		{
			if (!m_Active[i]) { continue; }

			ParticleLifetime & lifetime = m_Lifetime[i];
			lifetime.Elapsed += (float)ts;
			m_Active[i] = lifetime.Elapsed < lifetime.Duration;
		}
		
		for (int32 i = 0; i < limit; i++)
		{
			if (!m_Active[i]) { continue; }

			ParticleState & state = m_State[i];
			ParticleMotion & motion = m_Motion[i];
			state.Position += motion.Velocity * (float)ts;
			state.Rotation += motion.RotationSpeed * (float)ts;
		}
	}

	void ParticleSystem::OnRender()
	{
		GES_PROFILE_FUNCTION();
		int32 limit = m_Limit;
		for (int32 i = 0; i < limit; i++)
		{
			if (!m_Active[i]) { continue; }
			
			ParticleLifetime & lifetime = m_Lifetime[i];
			ParticleState & state = m_State[i];
			ParticleRendering & rendering = m_Rendering[i];

			float life = lifetime.Elapsed / lifetime.Duration;
			glm::vec4 color = glm::lerp(rendering.Color1, rendering.Color2, life);
			float size = glm::lerp(rendering.Size1, rendering.Size2, life);

			glm::vec3 drawPosition(state.Position.x, state.Position.y, 0.2f);
			GES::Renderer2D::DrawQuad(drawPosition, { size, size }, state.Rotation, color);
		}
	}
	#undef random_radius01
}
