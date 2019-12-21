#pragma once

// #define GES_BYPASS_VENDOR_HEADERS
#if defined(GES_BYPASS_VENDOR_HEADERS)
	#include <functional>
	#include <vector>
	#include <unordered_map>
	#include <string>
	#include <sstream>
	#include <fstream>

	#include <spdlog/spdlog.h>
	#include <spdlog/fmt/ostr.h>

	#include <glm/glm.hpp>
#endif

#include "GES/Core.h"
#include "GES/Core/Timestep.h"

#include "GES/Window.h"
#include "GES/Application.h"
#include "GES/Layer.h"
#include "GES/Log.h"

// #include "GES/KeyCodes.h"
// #include "GES/MouseCodes.h"
#include "GES/Input.h"

#include "GES/Events/Event.h"
#include "GES/Events/ApplicationEvent.h"
#include "GES/Events/KeyEvent.h"
#include "GES/Events/MouseEvent.h"

#include "GES/Renderer/Renderer.h"
#include "GES/Renderer/VertexArray.h"
#include "GES/Renderer/Buffer.h"
#include "GES/Renderer/Shader.h"
#include "GES/Renderer/Texture.h"

#include "GES/ImGuiLayer/ImGuiLayer.h"

#include "GES/Orthographic2dCameraController.h"

#include <imgui.h>

// ---- Entry Point -------
#include "GES/EntryPoint.h"
// ------------------------
