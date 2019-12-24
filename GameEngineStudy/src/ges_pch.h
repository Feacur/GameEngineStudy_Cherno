#pragma once

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

#if defined(GES_PLATFORM_WINDOWS)
	#include <Windows.h>
#endif
