#pragma once
#include "GES/ImGui/ImGuiBindings.h"

namespace GES
{
	class GlfwImGuiBindings : public ImGuiBindings
	{
	public:
		GlfwImGuiBindings();
		~GlfwImGuiBindings() override = default;

	protected:
		void InitImpl() override;
		void ShutdownImpl() override;
		void BeginImpl() override;
		void EndImpl() override;
	};
}
