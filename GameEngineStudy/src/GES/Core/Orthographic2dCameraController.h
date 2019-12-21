#pragma once

#include "GES/Renderer/Orthographic2dCamera.h"
#include "Timestep.h"

namespace GES
{
	class Event;
	class MouseScrolledEvent;
	class WindowResizeEvent;

	class Orthographic2dCameraController
	{
	public:
		Orthographic2dCameraController(float aspectRatio, bool rotation = false);

		void OnUpdate(Timestep ts);
		void OnEvent(Event & e);

		Orthographic2dCamera & GetCamera() { return m_Camera; }

	private:
		bool OnMouseScrolled(MouseScrolledEvent const & e);
		bool OnWindowResized(WindowResizeEvent const & e);

	private:
		float m_AspectRatio;
		float m_ZoomLevel = 1.0f;
		Orthographic2dCamera m_Camera;

		bool m_Rotation;

		glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
		float m_CameraRotatio = 0.0f;
		float m_CameraTranslationSpeed = 1.0f;
		float m_CameraRotationSpeed = 1.0f;
	};
}
