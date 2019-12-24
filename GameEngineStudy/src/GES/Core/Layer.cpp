#include "ges_pch.h"
#include "Layer.h"

#include "GES/Debug/Instrumentor.h"
#include "GES/Debug/Code.h"

namespace GES {
	Layer::Layer(const std::string& debugName)
		: m_DebugName(debugName)
	{
		GES_PROFILE_FUNCTION();
	}
}
