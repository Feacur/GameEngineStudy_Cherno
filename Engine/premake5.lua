project "Engine"
	-- location "."
	kind "StaticLib" -- or "SharedLib"
	language "C++"
	cdialect "C11"
	cppdialect "C++17"
	characterset ("ASCII") -- Default, Unicode, MBCS, ASCII

	Engine_to_root = path.getrelative(os.getcwd(), root_directory)
	Engine_target_location = (Engine_to_root .. "/" .. target_location)
	Engine_intermediate_location = (Engine_to_root .. "/" .. intermediate_location)
	targetdir (Engine_target_location .. "/%{prj.name}")
	objdir (Engine_intermediate_location .. "/%{prj.name}")
	implibdir (Engine_intermediate_location .. "/%{prj.name}")

	pchheader "ges_pch.h"
	pchsource ("src/ges_pch.cpp")
	defines "GES_PRECOMPILED_HEADER"

	files {
		"src/GES/**.h",
		"src/GES/**.cpp",
		"src/ges_pch.cpp",
		"%{engine_includes.spdlog}/spdlog/**.h",
		"%{engine_includes.glm}/glm/**.hpp",
		"%{engine_includes.glm}/glm/**.inl",
		"%{engine_includes.stb_image}/**.h",
		"%{engine_includes.stb_image}/**.cpp",
	}

	includedirs {
		"%{engine_includes.engine}",
		"%{engine_includes.glm}",
		"%{engine_includes.imgui}",
		"%{engine_includes.lua}",
		"%{engine_includes.spdlog}",
		"%{engine_includes.stb_image}",
	}

	links {
		"imgui",
		"lua",
	}

	postbuildcommands {
		("{COPY} \"%{prj.location}assets\" \"" .. Engine_target_location .. "/Sandbox/assets\""),
	}

	filter "system:windows"
		defines "WIN32_LEAN_AND_MEAN"

	filter "system:windows or macosx or linux or bsd"
		defines "GLFW_INCLUDE_NONE"
		links "GLFW"
		files {
			"src/Platform/GLFW/**.h",
			"src/Platform/GLFW/**.cpp",
		}
		includedirs "%{engine_includes.GLFW}"

	filter "system:windows or macosx or linux or bsd"
		links "Glad"
		files {
			"src/Platform/OpenGL/**.h",
			"src/Platform/OpenGL/**.cpp",
		}
		includedirs "%{engine_includes.Glad}"

	filter "kind:SharedLib"
		postbuildcommands {
			("{COPY} \"%{cfg.buildtarget.relpath}\" \"" .. Engine_target_location .. "/Sandbox/\""),
		}

	filter {}
