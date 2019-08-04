#pragma once

#include "GES/Layer.h"

struct ImGuiContext;

namespace GES {
	class GES_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer() override = default;

	public:
		void OnAttach() override;
		void OnDetach() override;
		void OnImGuiRender() override;

	public:
		void Begin();
		void End();
		inline ImGuiContext* GetImGuiContext() { return m_ImGuiContext; }

	private:
		float m_Time = 0;
		ImGuiContext * m_ImGuiContext;
	};
}
