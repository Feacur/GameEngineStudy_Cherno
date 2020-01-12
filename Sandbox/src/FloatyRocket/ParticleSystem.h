#pragma once
#include "GES.h"

#if !defined(GES_BYPASS_VENDOR_HEADERS)
	#include <vector>
#endif

namespace FloatyRocket
{
	struct ParticleProps;

	class ParticleSystem
	{
		public:
			ParticleSystem(s32 limit);
			~ParticleSystem();
			
			void Emit(ParticleProps const & props);
			void OnUpdate(GES::Timestep ts);
			void OnRender();

		private:
			struct ParticleLifetime
			{
				r32 Duration;
				r32 Elapsed;
			};

			struct ParticleState
			{
				glm::vec2 Position;
				r32 Rotation;
			};

			struct ParticleMotion
			{
				glm::vec2 Velocity;
				r32 RotationSpeed;
			};

			struct ParticleRendering
			{
				glm::vec4 Color1, Color2;
				r32 Size1, Size2;
			};

			u32 m_Random = 1u;

			s32 m_Index;
			s32 m_Limit;
			std::vector<bool> m_Active;
			std::vector<ParticleLifetime> m_Lifetime;
			std::vector<ParticleState> m_State;
			std::vector<ParticleMotion> m_Motion;
			std::vector<ParticleRendering> m_Rendering;
	};
}
