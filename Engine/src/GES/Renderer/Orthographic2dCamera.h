#pragma once
#include "GES/Core/Code.h"

#if !defined(GES_BYPASS_VENDOR_HEADERS)
	#include <glm/glm.hpp>
#endif

namespace GES
{
	class Orthographic2dCamera
	{
	public:
		Orthographic2dCamera(r32 left, r32 right, r32 bottom, r32 top);

	public:
		glm::vec3 const & GetPosition() const { return m_Position; }
		void SetPosition(glm::vec3 const & position) { m_Position = position; }

		r32 GetRotation() const { return m_RotationZ; }
		void SetRotation(r32 const & rotationZ) { m_RotationZ = rotationZ; }

		glm::mat4 const & GetViewMatrix() const { return m_ViewMatrix; }
		glm::mat4 const & GetProjectionMatrix() const { return m_ProjectionMatrix; }
		glm::mat4 const & GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }

		void SetProjection(r32 left, r32 right, r32 bottom, r32 top);
		void RecalculateViewMatrix();

	private:
		glm::vec3 m_Position;
		r32 m_RotationZ = 0;

	private:
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewProjectionMatrix;
	};
}
