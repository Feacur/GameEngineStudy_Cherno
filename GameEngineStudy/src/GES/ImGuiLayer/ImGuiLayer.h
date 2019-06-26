#pragma once

#include "GES/Layer.h"

#include "GES/Events/ApplicationEvent.h"
#include "GES/Events/KeyEvent.h"
#include "GES/Events/MouseEvent.h"

namespace GES {
	class GES_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		virtual ~ImGuiLayer();

	public:
		virtual void OnAttach();
		virtual void OnDetach();
		virtual void OnUpdate();
		virtual void OnEvent(Event& e);

	private:
		bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
		bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
		bool OnMouseMovedEvent(MouseMovedEvent& e);
		bool OnMouseScrolledEvent(MouseScrolledEvent& e);
		bool OnKeyPressedEvent(KeyPressedEvent& e);
		bool OnKeyReleasedEvent(KeyReleasedEvent& e);
		bool OnKeyTypedEvent(KeyTypedEvent& e);
		bool OnWindowResizedEvent(WindowResizeEvent& e);

	private:
		float m_Time = 0;
	};
}
