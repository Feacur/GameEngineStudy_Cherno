#pragma once
#include "Level.h"

#include <glm/gtc/matrix_transform.hpp>

// @Note: probably I should factor out a new submodule
//        instead of copy-pasting chunks around...
// https://github.com/Feacur/CustomEngineStudy/blob/master/code/shared/random.h
inline static r32 hash_01(u32 * state) {
	union { u32 x; r32 xf; };  // local unionized values
	x = (*state = *state * 16807U); // hash
	// @Note: might well mask fractional part with [0x007fffffU]
	x = (x >> 9) | 0x3f800000U;     // clamp to [1 .. 2) * (2^0)
	return xf - 1;                  // return [1 .. 2) - 1
}

static glm::vec4 HSVtoRGB(const glm::vec3& hsv) {
	int H = (int)(hsv.x * 360.0f);
	r64 S = hsv.y;
	r64 V = hsv.z;

	r64 C = S * V;
	r64 X = C * (1 - abs(fmod(H / 60.0, 2) - 1));
	r64 m = V - C;
	r64 Rs, Gs, Bs;

	if (H >= 0 && H < 60) {
		Rs = C;
		Gs = X;
		Bs = 0;
	}
	else if (H >= 60 && H < 120) {
		Rs = X;
		Gs = C;
		Bs = 0;
	}
	else if (H >= 120 && H < 180) {
		Rs = 0;
		Gs = C;
		Bs = X;
	}
	else if (H >= 180 && H < 240) {
		Rs = 0;
		Gs = X;
		Bs = C;
	}
	else if (H >= 240 && H < 300) {
		Rs = X;
		Gs = 0;
		Bs = C;
	}
	else {
		Rs = C;
		Gs = 0;
		Bs = X;
	}

	return { (Rs + m), (Gs + m), (Bs + m), 1.0f };
}

static bool PointInTri(const glm::vec2& p, glm::vec2& p0, const glm::vec2& p1, const glm::vec2& p2)
{
	r32 s = p0.y * p2.x - p0.x * p2.y + (p2.y - p0.y) * p.x + (p0.x - p2.x) * p.y;
	r32 t = p0.x * p1.y - p0.y * p1.x + (p0.y - p1.y) * p.x + (p1.x - p0.x) * p.y;

	if ((s < 0) != (t < 0))
		return false;

	r32 A = -p1.y * p2.x + p0.y * (p2.x - p1.x) + p0.x * (p1.y - p2.y) + p1.x * p2.y;

	return A < 0 ?
		(s <= 0 && s + t >= A) :
		(s >= 0 && s + t <= A);
}

namespace FloatyRocket
{
	#define random_01() hash_01(&m_Random)
	Level::Level()
	{
		m_Pillars.resize(5);
	}

	void Level::Reset()
	{
		m_IsCollision = false;
		m_PillarTarget = 30.0f;
		m_PillarIndex = 0;
		for (int i = 0; i < 5; i++)
			CreatePillar(i, i * 10.0f);
	}

	void Level::OnUpdate(GES::Timestep ts, glm::vec2 playerPos, r32 playerRot)
	{
		m_PillarHSV.x += 0.1f * ts;
		if (m_PillarHSV.x > 1.0f)
			m_PillarHSV.x = 0.0f;

		if (m_IsCollision) { return; }
		if (CollisionTest(playerPos, playerRot)) { m_IsCollision = true; return; }

		if (playerPos.x > m_PillarTarget)
		{
			CreatePillar(m_PillarIndex, m_PillarTarget + 20.0f);
			m_PillarIndex = ++m_PillarIndex % m_Pillars.size();
			m_PillarTarget += 10.0f;
		}
	}

	void Level::OnRender(GES::Ref<GES::Texture2D> texture, glm::vec2 playerPos)
	{
		glm::vec4 color = HSVtoRGB(m_PillarHSV);

		// Background
		// GES::Renderer2D::DrawQuad({ playerPos.x, 0.0f, 0.99f }, { 50.0f, 50.0f }, 0.0f, { 0.3f, 0.3f, 0.3f, 1.0f });

		// Floor and ceiling
		GES::Renderer2D::DrawQuad({ playerPos.x,  34.0f, 0.3f }, { 50.0f, 50.0f }, 0.0f, color);
		GES::Renderer2D::DrawQuad({ playerPos.x, -34.0f, 0.3f }, { 50.0f, 50.0f }, 0.0f, color);

		for (auto& pillar : m_Pillars)
		{
			GES::Renderer2D::DrawQuad(pillar.TopPosition, pillar.TopScale, glm::radians(180.0f), color, texture);
			GES::Renderer2D::DrawQuad(pillar.BottomPosition, pillar.BottomScale, 0.0f, color, texture);
		}
	}

	void Level::CreatePillar(int index, r32 offset)
	{
		Pillar& pillar = m_Pillars[index];

		r32 center = random_01() * 35.0f - 17.5f;
		r32 gap = 2.0f + random_01() * 5.0f;

		pillar.TopPosition.x = offset;
		pillar.TopPosition.y = 10.0f - ((10.0f - center) * 0.2f) + gap * 0.5f;
		pillar.TopPosition.z = 0.95f - index * 0.1f;

		pillar.BottomPosition.x = offset;
		pillar.BottomPosition.y = -10.0f - ((-10.0f - center) * 0.2f) - gap * 0.5f;
		pillar.BottomPosition.z = 0.90f - index * 0.1f;
	}

	bool Level::CollisionTest(glm::vec2 playerPos, r32 playerRot)
	{
		if (glm::abs(playerPos.y) > 8.5f)
			return true;

		glm::vec4 playerVertices[4] = {
			{ -0.5f, -0.5f, 0.0f, 1.0f },
			{  0.5f, -0.5f, 0.0f, 1.0f },
			{  0.5f,  0.5f, 0.0f, 1.0f },
			{ -0.5f,  0.5f, 0.0f, 1.0f }
		};

		glm::vec4 playerTransformedVerts[4];
		for (int i = 0; i < 4; i++)
		{
			playerTransformedVerts[i] = glm::translate(glm::mat4(1.0f), { playerPos.x, playerPos.y, 0.0f })
				* glm::rotate(glm::mat4(1.0f), playerRot, { 0.0f, 0.0f, 1.0f })
				* glm::scale(glm::mat4(1.0f), { 1.0f, 1.3f, 1.0f })
				* playerVertices[i];
		}


		// To match Triangle.png (each corner is 10% from the texture edge)
		glm::vec4 pillarVertices[3] = {
			{ -0.5f + 0.1f, -0.5f + 0.1f, 0.0f, 1.0f },
			{  0.5f - 0.1f, -0.5f + 0.1f, 0.0f, 1.0f },
			{  0.0f + 0.0f,  0.5f - 0.1f, 0.0f, 1.0f },
		};

		for (auto& p : m_Pillars)
		{
			glm::vec2 tri[3];
			
			// Top pillars
			for (int i = 0; i < 3; i++)
			{
				tri[i] = glm::translate(glm::mat4(1.0f), { p.TopPosition.x, p.TopPosition.y, 0.0f })
					* glm::rotate(glm::mat4(1.0f), glm::radians(180.0f), { 0.0f, 0.0f, 1.0f })
					* glm::scale(glm::mat4(1.0f), { p.TopScale.x, p.TopScale.y, 1.0f })
					* pillarVertices[i];
			}

			for (auto& vert : playerTransformedVerts)
			{
				if (PointInTri({ vert.x, vert.y }, tri[0], tri[1], tri[2]))
					return true;
			}

			// Bottom pillars
			for (int i = 0; i < 3; i++)
			{
				tri[i] = glm::translate(glm::mat4(1.0f), { p.BottomPosition.x, p.BottomPosition.y, 0.0f })
					* glm::scale(glm::mat4(1.0f), { p.BottomScale.x, p.BottomScale.y, 1.0f })
					* pillarVertices[i];
			}

			for (auto& vert : playerTransformedVerts)
			{
				if (PointInTri({ vert.x, vert.y }, tri[0], tri[1], tri[2]))
					return true;
			}

		}
		return false;
	}
}
