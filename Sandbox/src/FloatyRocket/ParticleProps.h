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
		r32 Rotation, RotationVariation;
		r32 RotationSpeed, RotationSpeedVariation;
		glm::vec4 Color1, Color2;
		r32 Size1, Size2, Size1Variation;
		r32 LifeTime;
	};
}
