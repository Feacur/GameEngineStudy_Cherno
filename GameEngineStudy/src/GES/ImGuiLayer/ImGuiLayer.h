#pragma once

#include "GES/Layer.h"

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
		virtual void OnEvent(Event& event);

	private:
		float m_Time = 0;
	};
}
