#pragma once
#include "GES/Core/Code.h"

#include "GES/Core/Layer.h"

struct ImGuiContext;

namespace GES {
	class GES_DLL ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer() override = default;

	public:
		void OnAttach() override;
		void OnDetach() override;
		// void OnImGuiRender() override;

	public:
		void Begin();
		void End(r32 width, r32 height);
		inline ImGuiContext* GetImGuiContext() { return m_ImGuiContext; }

	private:
		r32 m_Time = 0;
		ImGuiContext * m_ImGuiContext;
	};
}
