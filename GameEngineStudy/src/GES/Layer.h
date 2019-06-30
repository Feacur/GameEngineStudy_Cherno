#pragma once

#include "GES/Core.h"
#include "GES/Events/Event.h"

#ifdef GES_SHARED
#pragma warning(push)
#pragma warning(disable: 4251)
#endif
namespace GES {
	class GES_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer() = default;

	public:
		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnEvent(Event& event) {}

	public:
		virtual void OnImGuiRender() {}

		inline const std::string& GetName() const { return m_DebugName; }
	protected:
		std::string m_DebugName;
	};
}

#ifdef GES_SHARED
#pragma warning(pop)
#endif
