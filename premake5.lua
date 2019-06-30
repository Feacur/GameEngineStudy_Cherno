workspace "GameEngineStudy"
	-- toolset ("msc")
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
			-- "4521", -- 'identifier' : class 'type' needs to have dll-interface to be used by clients of class 'type2'
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

-- Include directories relative to the root folder (solution directory)
include_directories = {}
include_directories["GES"]    = enginename .. "/src"
include_directories["spdlog"] = enginename .. "/vendor/spdlog/include"
include_directories["GLFW"]   = enginename .. "/vendor/GLFW/include"
include_directories["Glad"]   = enginename .. "/vendor/Glad/include"
include_directories["imgui"]  = enginename .. "/vendor/imgui"
include_directories["glm"]    = enginename .. "/vendor/glm"

root_directory = os.getcwd()

group "Dependecies"
include "GameEngineStudy/vendor/premake5_GLFW.lua"
include "GameEngineStudy/vendor/premake5_Glad.lua"
include "GameEngineStudy/vendor/premake5_imgui.lua"
group ""

project "GameEngineStudy"
	location "GameEngineStudy"
	kind "StaticLib"
	language "C++"
	cdialect "C11"
	cppdialect "C++17"
	characterset ("Unicode")

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "ges_pch.h"
	pchsource (enginename .. "/src/ges_pch.cpp")

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		-- "%{include_directories.spdlog}/spdlog/**.h",
		-- "%{include_directories.glm}/glm/**.hpp",
		-- "%{include_directories.glm}/glm/**.inl",
	}

	includedirs {
		"%{include_directories.GES}",
		"%{include_directories.spdlog}",
		"%{include_directories.GLFW}",
		"%{include_directories.Glad}",
		"%{include_directories.imgui}",
		"%{include_directories.glm}",
	}

	filter "system:windows"
		staticruntime "Off"
		systemversion "latest"

		defines {
			"GES_PLATFORM_WINDOWS",
			-- "GES_BUILD_DLL", -- if specified [kind "SharedLib"]
			"GES_BUILD_NONE", -- if specified [kind "StaticLib"]
			"GLFW_INCLUDE_NONE",
			"_CRT_SECURE_NO_WARNINGS"
		}

		links {
			"GLFW",
			"Glad",
			"imgui",
			"opengl32.lib",
		}

		-- if specified [kind "SharedLib"]
		-- postbuildcommands {
		-- 	("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")
		-- }

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
		"%{include_directories.GES}",
		"%{include_directories.spdlog}",
		"%{include_directories.imgui}",
		"%{include_directories.glm}",
	}

	links {
		"GameEngineStudy",
	}

	filter "system:windows"
		staticruntime "Off"
		systemversion "latest"

		defines {
			"GES_PLATFORM_WINDOWS",
			"GES_BUILD_NONE", -- if specified [kind "StaticLib"] for the GameEngineStudy
			-- "IMGUI_API=__declspec(dllimport)", -- if specified [kind "SharedLib"] for the GameEngineStudy
		}
