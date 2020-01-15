#pragma once
#include "GES/Core/Code.h"

namespace GES
{
	class GES_DLL ImGuiBindings
	{
	public:
		virtual ~ImGuiBindings() = default;

	public:
		inline static void Init() { s_Instance->InitImpl(); }
		inline static void Shutdown() { s_Instance->ShutdownImpl(); }
		inline static void Begin() { s_Instance->BeginImpl(); }
		inline static void End() { s_Instance->EndImpl(); }

	protected:
		virtual void InitImpl() = 0;
		virtual void ShutdownImpl() = 0;
		virtual void BeginImpl() = 0;
		virtual void EndImpl() = 0;
	
	protected:
		static ImGuiBindings * s_Instance;
	};
}
