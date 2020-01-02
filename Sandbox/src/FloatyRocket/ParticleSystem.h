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
			ParticleSystem(int32 limit);
			~ParticleSystem();
			
			void Emit(ParticleProps const & props);
			void OnUpdate(GES::Timestep ts);
			void OnRender();

		private:
			struct ParticleLifetime
			{
				float Duration;
				float Elapsed;
			};

			struct ParticleState
			{
				glm::vec2 Position;
				float Rotation;
			};

			struct ParticleMotion
			{
				glm::vec2 Velocity;
				float RotationSpeed;
			};

			struct ParticleRendering
			{
				glm::vec4 Color1, Color2;
				float Size1, Size2;
			};

			uint32 m_Random = 1u;

			int32 m_Index;
			int32 m_Limit;
			std::vector<bool> m_Active;
			std::vector<ParticleLifetime> m_Lifetime;
			std::vector<ParticleState> m_State;
			std::vector<ParticleMotion> m_Motion;
			std::vector<ParticleRendering> m_Rendering;
	};
}
