#include "ges_pch.h"
#include "LayerStack.h"

#include "Layer.h"

#include "GES/Debug/Instrumentor.h"
#include "GES/Debug/Code.h"

namespace GES {
	LayerStack::~LayerStack()
	{
		GES_PROFILE_FUNCTION();
		for (Layer* layer : m_Layers) {
			layer->OnDetach();
			delete layer;
		}
	}

	void LayerStack::PushLayer(Layer* layer)
	{
		GES_PROFILE_FUNCTION();
		m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, layer);
		m_LayerInsertIndex++;
		layer->OnAttach();
	}

	void LayerStack::PushOverlay(Layer* overlay)
	{
		GES_PROFILE_FUNCTION();
		m_Layers.emplace_back(overlay);
		overlay->OnAttach();
	}

	void LayerStack::PopLayer(Layer* layer)
	{
		GES_PROFILE_FUNCTION();
		auto end = m_Layers.begin() + m_LayerInsertIndex;
		auto it = std::find(m_Layers.begin(), end, layer);
		if (it != end)
		{
			layer->OnDetach();
			m_Layers.erase(it);
			m_LayerInsertIndex--;
		}
	}

	void LayerStack::PopOverlay(Layer* overlay)
	{
		GES_PROFILE_FUNCTION();
		auto it = std::find(m_Layers.begin(), m_Layers.begin() + m_LayerInsertIndex, overlay);
		if (it != m_Layers.end())
		{
			overlay->OnDetach();
			m_Layers.erase(it);
		}
	}
}
