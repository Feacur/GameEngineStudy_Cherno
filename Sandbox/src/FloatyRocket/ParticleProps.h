#pragma once
#include "GES.h"

#if !defined(GES_BYPASS_VENDOR_HEADERS)
	#include <glm/glm.hpp>
#endif

namespace FloatyRocket
{
	struct ParticleProps
	{
		glm::vec2 Position;
		glm::vec2 Velocity, VelocityVariation;
		float Rotation, RotationVariation;
		float RotationSpeed, RotationSpeedVariation;
		glm::vec4 Color1, Color2;
		float Size1, Size2, Size1Variation;
		float LifeTime;
	};
}
