#pragma once

#include "GES/Core.h"
#include "GES/Events/Event.h"

#pragma warning(push)
#pragma warning(disable: 4251)
namespace GES {
	class GES_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnEvent(Event& event) {}

		inline const std::string& GetName() const { return m_DebugName; }
	protected:
		std::string m_DebugName;
	};
}
#pragma warning(pop)
