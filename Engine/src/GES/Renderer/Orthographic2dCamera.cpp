#include "ges_pch.h"
#include "Orthographic2dCamera.h"

#include "GES/Debug/Instrumentor.h"
#include "GES/Debug/Code.h"

#pragma warning(push)
#pragma warning(disable: 4127) // conditional expression is constant
#include <glm/gtc/matrix_transform.hpp>
#pragma warning(pop)

namespace GES
{
	Orthographic2dCamera::Orthographic2dCamera(float left, float right, float bottom, float top)
		: m_ProjectionMatrix(glm::ortho(left, right, bottom, top, 0.0f, 1.0f))
		, m_Position(0, 0, 0)
	{
		GES_PROFILE_FUNCTION();
	}

	void Orthographic2dCamera::SetProjection(float left, float right, float bottom, float top)
	{
		GES_PROFILE_FUNCTION();
		m_ProjectionMatrix = glm::ortho(left, right, bottom, top, 0.0f, 1.0f);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void Orthographic2dCamera::RecalculateViewMatrix()
	{
		GES_PROFILE_FUNCTION();
		glm::mat4 transform =
			glm::translate(glm::mat4(1.0f), m_Position) *
			glm::rotate(glm::mat4(1.0f), m_RotationZ, glm::vec3(0, 0, 1));
		m_ViewMatrix = glm::inverse(transform);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}
}
