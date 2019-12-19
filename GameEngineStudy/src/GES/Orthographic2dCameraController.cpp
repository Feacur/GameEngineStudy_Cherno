#include "ges_pch.h"
#include "Orthographic2dCameraController.h"

#include "GES/Input.h"
#include "GES/Events/ApplicationEvent.h"
#include "GES/Events/MouseEvent.h"

namespace GES
{
	Orthographic2dCameraController::Orthographic2dCameraController(float aspectRatio, bool rotation)
		: m_AspectRatio(aspectRatio)
		, m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel)
		, m_Rotation(rotation) {}

	void Orthographic2dCameraController::OnUpdate(Timestep ts)
	{
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
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(BIND_EVENT_FN(Orthographic2dCameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(Orthographic2dCameraController::OnWindowResized));
	}

	bool Orthographic2dCameraController::OnMouseScrolled(MouseScrolledEvent const & e)
	{
		m_ZoomLevel -= e.GetYOffset() * 0.25f;
		m_ZoomLevel = std::clamp(m_ZoomLevel, 0.25f, 4.0f);
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}

	bool Orthographic2dCameraController::OnWindowResized(WindowResizeEvent const & e)
	{
		m_AspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}
}
