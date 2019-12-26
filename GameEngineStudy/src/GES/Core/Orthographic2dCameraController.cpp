#include "ges_pch.h"
#include "Orthographic2dCameraController.h"

// #include "KeyCodes.h"
// #include "MouseCodes.h"
#include "Input.h"

#include "GES/Debug/Instrumentor.h"
#include "GES/Debug/Code.h"

#include "GES/Events/Event.h"
#include "GES/Events/ApplicationEvent.h"
#include "GES/Events/MouseEvent.h"

namespace GES
{
	Orthographic2dCameraController::Orthographic2dCameraController(float aspectRatio, bool rotation)
		: m_AspectRatio(aspectRatio)
		, m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel)
		, m_Rotation(rotation)
	{
		GES_PROFILE_FUNCTION();
	}

	void Orthographic2dCameraController::OnUpdate(Timestep ts)
	{
		GES_PROFILE_FUNCTION();
		float positionDelta = m_CameraTranslationSpeed * ts;
		float rotationDelta = m_CameraRotationSpeed * ts;

		auto cameraPosition = m_Camera.GetPosition();
		auto cameraRotation = m_Camera.GetRotation();

		if (GES::Input::IsKeyPressed(GES_KEY_A)) {
			cameraPosition.x -= positionDelta;
		}

		if (GES::Input::IsKeyPressed(GES_KEY_D)) {
			cameraPosition.x += positionDelta;
		}

		if (GES::Input::IsKeyPressed(GES_KEY_S)) {
			cameraPosition.y -= positionDelta;
		}

		if (GES::Input::IsKeyPressed(GES_KEY_W)) {
			cameraPosition.y += positionDelta;
		}

		if (GES::Input::IsKeyPressed(GES_KEY_Q)) {
			cameraRotation -= rotationDelta;
		}

		if (GES::Input::IsKeyPressed(GES_KEY_E)) {
			cameraRotation += rotationDelta;
		}

		m_Camera.SetPosition(cameraPosition);
		m_Camera.SetRotation(cameraRotation);
		m_Camera.RecalculateViewMatrix();
	}

	void Orthographic2dCameraController::OnEvent(Event & e)
	{
		GES_PROFILE_FUNCTION();
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(BIND_EVENT_FN(Orthographic2dCameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(Orthographic2dCameraController::OnWindowResized));
	}

	bool Orthographic2dCameraController::OnMouseScrolled(MouseScrolledEvent const & e)
	{
		GES_PROFILE_FUNCTION();
		m_ZoomLevel -= e.GetYOffset() * 0.1f;
		m_ZoomLevel = std::clamp(m_ZoomLevel, 0.25f, 10.0f);
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}

	bool Orthographic2dCameraController::OnWindowResized(WindowResizeEvent const & e)
	{
		GES_PROFILE_FUNCTION();
		m_AspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}
}
