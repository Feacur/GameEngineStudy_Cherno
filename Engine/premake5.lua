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

	files {
		"src/**.h",
		"src/**.cpp",
		"%{include_directories.spdlog}/spdlog/**.h",
		"%{include_directories.glm}/glm/**.hpp",
		"%{include_directories.glm}/glm/**.inl",
		"%{include_directories.stb_image}/**.h",
		"%{include_directories.stb_image}/**.cpp",
	}

	includedirs {
		"%{include_directories.engine}",
		"%{include_directories.Glad}",
		"%{include_directories.GLFW}",
		"%{include_directories.glm}",
		"%{include_directories.imgui}",
		"%{include_directories.lua}",
		"%{include_directories.spdlog}",
		"%{include_directories.stb_image}",
	}

	defines {
		"GLFW_INCLUDE_NONE",
	}

	links {
		"GLFW",
		"Glad",
		"imgui",
		"lua",
	}
	
	postbuildcommands {
		("{COPY} \"%{prj.location}assets\" \"" .. Engine_target_location .. "/Sandbox/assets\""),
	}

	filter "kind:SharedLib"
		postbuildcommands {
			("{COPY} \"%{cfg.buildtarget.relpath}\" \"" .. Engine_target_location .. "/Sandbox/\""),
		}

