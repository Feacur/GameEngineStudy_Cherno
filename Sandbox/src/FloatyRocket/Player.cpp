#include "Player.h"

#include "ParticleProps.h"
#include "ParticleSystem.h"

#include <glm/gtc/matrix_transform.hpp>

namespace FloatyRocket
{
	constexpr static ParticleProps ConstructFireParticleProps()
	{
		ParticleProps props = {};
		props.Velocity = { -2.0f, 0.0f };
		props.VelocityVariation = { 3.0f, 1.0f };
		props.Size1 = 0.5f;
		props.Size1Variation = 0.3f;
		props.Color1 = { 0.99f, 0.43f, 0.17f, 1.0f };
		props.Color2 = { 0.99f, 0.83f, 0.48f , 0.0f };
		props.LifeTime = 1.0f;
		return props;
	}
	
	constexpr static ParticleProps ConstructSmokeParticleProps()
	{
		ParticleProps props = {};
		props.Velocity = { -2.0f, 0.0f };
		props.VelocityVariation = { 4.0f, 2.0f };
		props.Size1 = 0.35f;
		props.Size1Variation = 0.15f;
		props.Size2 = 0.7f;
		props.Color1 = { 0.8f, 0.8f, 0.8f, 1.0f };
		props.Color2 = { 0.6f, 0.6f, 0.6f, 0.0f };
		props.LifeTime = 4.0f;
		return props;
	}

	void Player::Reset()
	{
		m_ParticleFireElapsed = 0.0f;
		m_ParticleSmokeElapsed = 0.0f;
		m_Position = { -10.0f, 0.0f };
		m_Velocity = { 5.0f, 0.0f };
	}

	void Player::OnUpdate(GES::Timestep ts, ParticleSystem & particleSystem)
	{
		static ParticleProps FireParticle = ConstructFireParticleProps();
		static ParticleProps SmokeParticle = ConstructSmokeParticleProps();
		static float const m_EnginePower = 31.25f;
		static float const m_Gravity = 25.0f;

		m_ParticleSmokeElapsed += (float)ts;

		if (GES::Input::IsKeyPressed(GES_KEY_SPACE))
		{
			m_ParticleFireElapsed += (float)ts;
			if (m_Velocity.y < 0.0f)
			{
				m_Velocity.y += m_EnginePower * 3.0f * (float)ts;
			}
			else
			{
				m_Velocity.y += m_EnginePower * (float)ts;
			}
		}
		else
		{
			m_Velocity.y -= m_Gravity * (float)ts;
		}

		m_Velocity.y = glm::clamp(m_Velocity.y, -20.0f, 20.0f);
		m_Position += m_Velocity * (float)ts;

		if (m_ParticleFireElapsed >= m_ParticleFirePeriod)
		{
			m_ParticleFireElapsed -= m_ParticleFirePeriod;

			glm::vec2 emissionPoint = { 0.0f, -0.6f };
			glm::vec4 rotated = glm::rotate(glm::mat4(1.0f), GetRotation(), { 0.0f, 0.0f, 1.0f }) * glm::vec4(emissionPoint, 0.0f, 1.0f);

			FireParticle.Position = m_Position + glm::vec2{ rotated.x, rotated.y };
			FireParticle.Velocity = -m_Velocity * 0.2f;
			particleSystem.Emit(FireParticle);
		}

		if (m_ParticleSmokeElapsed >= m_ParticleSmokePeriod)
		{
			m_ParticleSmokeElapsed -= m_ParticleSmokePeriod;

			SmokeParticle.Position = m_Position;
			SmokeParticle.Velocity = -m_Velocity * 0.05f;
			particleSystem.Emit(SmokeParticle);
		}
	}

	void Player::OnRender(GES::Ref<GES::Texture2D> texture)
	{
		static glm::vec2 const size = { 1.0f, 1.3f };
		glm::vec2 playerPos = GetPosition();
		glm::vec3 drawPosition(playerPos.x, playerPos.y, 0.1f);
		GES::Renderer2D::DrawQuad(drawPosition, size, GetRotation(), texture);
	}
}
