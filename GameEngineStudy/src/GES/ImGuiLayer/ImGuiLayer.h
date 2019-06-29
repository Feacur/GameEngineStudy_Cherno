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
		~ImGuiLayer() override;

	public:
		void OnAttach() override;
		void OnDetach() override;
		void OnImGuiRender() override;

	public:
		void Begin();
		void End();

	private:
		float m_Time = 0;
	};
}
