#pragma once
#include "GES.h"

namespace FloatyRocket
{
	class Level
	{
	public:
		Level();

		void Reset();
		void OnUpdate(GES::Timestep ts, glm::vec2 playerPos, float playerRot);
		void OnRender(GES::Ref<GES::Texture2D> texture, glm::vec2 playerPos);

		bool IsCollision() { return m_IsCollision; }

	private:
		void CreatePillar(int index, float offset);
		bool CollisionTest(glm::vec2 playerPos, float playerRot);

	private:
		struct Pillar
		{
			glm::vec3 TopPosition = { 0.0f, 10.0f, 0.0f };
			glm::vec2 TopScale = { 15.0f, 20.0f };

			glm::vec3 BottomPosition = { 10.0f, 10.0f, 0.0f};
			glm::vec2 BottomScale = { 15.0f, 20.0f };
		};

		uint32 m_Random = 1u;

		bool m_IsCollision;

		float m_PillarTarget = 30.0f;
		int m_PillarIndex = 0;
		std::vector<Pillar> m_Pillars;
		glm::vec3 m_PillarHSV = { 0.0f, 0.8f, 0.8f };
	};
}
