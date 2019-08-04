#pragma once

#include <glm/glm.hpp>

namespace GES
{
	class Orthographic2dCamera
	{
	public:
		Orthographic2dCamera(float left, float right, float bottom, float top);

	public:
		glm::vec3 const & GetPosition() const { return m_Position; }
		void SetPosition(glm::vec3 const & position) { m_Position = position; }

		float GetRotation() const { return m_RotationZ; }
		void SetRotation(float const & rotationZ) { m_RotationZ = rotationZ; }

		glm::mat4 const & GetViewMatrix() const { return m_ViewMatrix; }
		glm::mat4 const & GetProjectionMatrix() const { return m_ProjectionMatrix; }
		glm::mat4 const & GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }

		void RecalculateViewMatrix();

	private:
		glm::vec3 m_Position;
		float m_RotationZ = 0;

	private:
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewProjectionMatrix;
	};
}
