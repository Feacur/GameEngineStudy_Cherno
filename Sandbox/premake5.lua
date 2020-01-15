project "Sandbox"
	-- location "."
	kind "ConsoleApp"
	-- entrypoint "mainCRTStartup"
	language "C++"
	cdialect "C11"
	cppdialect "C++17"
	characterset ("ASCII") -- Default, Unicode, MBCS, ASCII

	Sandbox_to_root = path.getrelative(os.getcwd(), root_directory)
	targetdir (Sandbox_to_root .. "/" .. target_location .. "/%{prj.name}")
	objdir (Sandbox_to_root .. "/" .. intermediate_location .. "/%{prj.name}")
	implibdir (Sandbox_to_root .. "/" .. intermediate_location .. "/%{prj.name}")

	files {
		"src/**.h",
		"src/**.cpp",
	}

	includedirs {
		Sandbox_to_root .. "/Engine/%{include_directories.engine}",
		Sandbox_to_root .. "/Engine/%{include_directories.glm}",
		Sandbox_to_root .. "/Engine/%{include_directories.imgui}",
		Sandbox_to_root .. "/Engine/%{include_directories.lua}",
		Sandbox_to_root .. "/Engine/%{include_directories.spdlog}",
	}

	links {
		"Engine",
	}

	postbuildcommands {
		("{COPY} \"%{prj.location}assets\" \"%{cfg.buildtarget.directory}assets\"")
	}

	defines {
		-- "GES_SYMBOLS_SHARE", -- if specified [kind "SharedLib"] for the Engine
	}

	filter "toolset:msc*"
		defines {
			-- "IMGUI_API=__declspec(dllimport)", -- if specified [kind "SharedLib"] for the Engine
		}
