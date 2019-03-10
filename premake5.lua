workspace "GameEngineStudy"
	toolset ("msc")
	architecture "x64"
	startproject "Sandbox"
	warnings "Extra"
	flags { "FatalWarnings", "NoMinimalRebuild" }
	floatingpoint "Fast"
	floatingpointexceptions "off"
	exceptionhandling "Off"
	rtti "Off"

	configurations {
		"Debug",
		"Development",
		"Shipping"
	}

	filter "toolset:msc*"
		disablewarnings {
			"4201", -- nameless struct/union (suppress)
			"4189", -- local variable is initialized but not referenced (suppress)
			"4100", -- unreferenced formal parameter (suppress)
			"4530", -- C++ exception handling was used but -EHsc was not selected (suppress)
		}
		-- buildoptions {
		-- 	"-Bt+",
		-- 	"-d2cgsummary",
		-- 	"-d1reportTime",
		-- }
		-- linkoptions {
		-- 	"-time+",
		-- }

	filter "toolset:gcc*"
		disablewarnings { "unused-variable", "unused-parameter", "missing-field-initializers" }

	filter "toolset:clang*"
		disablewarnings { "unused-variable", "unused-parameter", "missing-field-initializers" }

	filter "configurations:Debug"
		defines "DEBUG"
		symbols "On"
		optimize "Off"

	filter "configurations:Development"
		defines "DEVELOPMENT"
		symbols "On"
		optimize "On"

	filter "configurations:Shipping"
		defines "SHIPPING"
		symbols "Off"
		optimize "On"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
enginename = "GameEngineStudy"

-- Include directories relative to root folder (solution directory)
include_directories = {}
include_directories["GLFW"] = "GameEngineStudy/vendor/GLFW/include"

root_directory = os.getcwd()
include "GameEngineStudy/vendor/premake5_GLFW.lua"

project "GameEngineStudy"
	location "GameEngineStudy"
	kind "SharedLib"
	language "C++"
	cdialect "C11"
	cppdialect "C++17"
	characterset ("Unicode")

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "ges_pch.h"
	pchsource "GameEngineStudy/src/ges_pch.cpp"

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs {
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{include_directories.GLFW}",
	}

	filter "system:windows"
		staticruntime "On"
		systemversion "latest"

		defines {
			"GES_PLATFORM_WINDOWS",
			"GES_BUILD_DLL",
		}

		links {
			"GLFW",
			"opengl32.lib",
		}

		postbuildcommands {
			("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")
		}

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cdialect "C11"
	cppdialect "C++17"
	characterset ("Unicode")

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}

	includedirs {
		(enginename .. "/src"),
		(enginename .. "/vendor/spdlog/include"),
	}

	links {
		"GameEngineStudy",
	}

	filter "system:windows"
		staticruntime "On"
		systemversion "latest"

		defines {
			"GES_PLATFORM_WINDOWS",
		}
