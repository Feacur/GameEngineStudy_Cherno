#pragma once

// #define GES_BYPASS_VENDOR_HEADERS
#if defined(GES_BYPASS_VENDOR_HEADERS)
	#include <functional>
	#include <algorithm>

	#include <chrono>
	#include <thread>

	#include <vector>
	#include <unordered_map>
	#include <string>

	#include <sstream>
	#include <fstream>

	#include <spdlog/spdlog.h>
	#include <spdlog/fmt/ostr.h>

	#include <glm/glm.hpp>
#endif

#include "GES/Core/Code.h"
#include "GES/Core/Timestep.h"
#include "GES/Core/Window.h"
#include "GES/Core/Application.h"
#include "GES/Core/Layer.h"

#include "GES/Debug/Log.h"
// #include "GES/Debug/ScopedProfiler.h"
#include "GES/Debug/Instrumentor.h"

// #include "GES/Core/KeyCodes.h"
// #include "GES/Core/MouseCodes.h"
#include "GES/Core/Input.h"

#include "GES/Events/Event.h"
#include "GES/Events/ApplicationEvent.h"
#include "GES/Events/KeyEvent.h"
#include "GES/Events/MouseEvent.h"

#include "GES/Renderer/RendererCommand.h"
#include "GES/Renderer/Renderer.h"
#include "GES/Renderer/Renderer2D.h"
#include "GES/Renderer/VertexArray.h"
#include "GES/Renderer/Buffer.h"
#include "GES/Renderer/Shader.h"
#include "GES/Renderer/Texture.h"

#include "GES/ImGuiLayer/ImGuiLayer.h"

#include "GES/Core/Orthographic2dCameraController.h"
