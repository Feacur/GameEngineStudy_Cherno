#pragma once

#include "GES/Core.h"

#include <vector>

#ifdef GES_SHARED
#pragma warning(push)
#pragma warning(disable: 4251)
#endif
namespace GES {
	class Layer;

	class GES_API LayerStack
	{
	public:
		LayerStack() = default;
		~LayerStack();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* overlay);

		std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
		std::vector<Layer*>::iterator end() { return m_Layers.end(); }
	private:
		std::vector<Layer*> m_Layers;
		uint32 m_LayerInsertIndex = 0;
	};
}
#ifdef GES_SHARED
#pragma warning(pop)
#endif
