include "./premake5_customizations.lua"

workspace "GameEngineStudy"
	-- toolset ("msc")
	architecture "x86_64"
	systemversion "latest"
	startproject "Sandbox"
	warnings "Extra"
	editandcontinue "Off"
	flags {
		"FatalWarnings",
		"NoMinimalRebuild",
		"MultiProcessorCompile",
		"NoIncrementalLink",
		-- "LinkTimeOptimization",
		-- "Maps",
	}
	floatingpoint "Fast"
	floatingpointexceptions "off"
	exceptionhandling "Off"
	rtti "Off"

	configurations {
		"Debug",
		"Development",
		"Shipping",
	}

	defines {
		"GLM_FORCE_DEPTH_ZERO_TO_ONE",
		"GLM_FORCE_LEFT_HANDED",
		"_CRT_SECURE_NO_WARNINGS", -- @Note: might want to enable this only locally
	}

	filter "toolset:msc*"
		disablewarnings {
			"4201", -- nameless struct/union (suppress)
			"4189", -- local variable is initialized but not referenced (suppress)
			"4100", -- unreferenced formal parameter (suppress)
			"4530", -- C++ exception handling was used but -EHsc was not selected (suppress)
			"4702", -- unreachable code (suppress) -- fmt from spdlog causes it
			-- "4521", -- 'identifier' : class 'type' needs to have dll-interface to be used by clients of class 'type2'
			-- "4312", -- 'operation' : conversion from 'type1' to 'type2' of greater size
			-- "4127", -- conditional expression is constant
		}
		-- buildoptions {
		-- 	"-Bt+",
		-- 	"-d2cgsummary",
		-- 	"-d1reportTime",
		-- }
		-- linkoptions {
		-- 	"-time+",
		-- }

	filter "kind:StaticLib"
		defines "GES_STATIC_LIBRARY"

	filter "kind:SharedLib"
		defines {
			"GES_SHARED_LIBRARY",
			"GES_SYMBOLS_SHARE",
		}

	filter "kind:ConsoleApp or WindowedApp"
		defines "GES_APPLICATION"

	filter "configurations:Debug"
		defines "GES_DEBUG"
		staticruntime "Off"
		runtime "Debug"
		symbols "Full" -- On, Full
		optimize "Off" -- Off, Debug

	filter "configurations:Development"
		defines "GES_DEVELOPMENT"
		staticruntime "Off"
		runtime "Release"
		symbols "FastLink" -- On, FastLink
		optimize "On" -- On, Debug

	filter "configurations:Shipping"
		-- either bundle CRT (vcruntime140.dll, etc.)
		-- or build with [staticruntime "On"]
		defines "GES_SHIPPING"
		staticruntime "Off"
		runtime "Release"
		symbols "Off"
		optimize "On" -- On, Size, Speed, Full

	filter {}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
target_location = ("bin/" .. outputdir)
intermediate_location = ("bin-int/" .. outputdir)
enginename = "Engine"

engine_includes = {}
engine_includes["engine"] = "src"
engine_includes["Glad"]   = "vendor/Glad/include"
engine_includes["GLFW"]   = "vendor/GLFW/include"
engine_includes["glm"]    = "vendor/glm"
engine_includes["imgui"]  = "vendor/imgui"
engine_includes["lua"]    = "vendor/lua/src"
engine_includes["spdlog"] = "vendor/spdlog/include"
engine_includes["stb_image"] = "vendor/stb_image"

root_directory = os.getcwd()

group "Dependecies"
include "Engine/vendor/premake5_Glad.lua"
include "Engine/vendor/premake5_GLFW.lua"
include "Engine/vendor/premake5_imgui.lua"
include "Engine/vendor/premake5_lua.lua"
group ""

include "Engine/premake5.lua"
include "Sandbox/premake5.lua"
