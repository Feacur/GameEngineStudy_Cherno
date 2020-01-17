project "imgui"
	kind "StaticLib"
	language "C"
	cdialect "C99"
	cppdialect "C++11"
	characterset ("ASCII") -- Default, Unicode, MBCS, ASCII
	warnings "Default"
	removeflags { "FatalWarnings" }
	
	symbols "Off"
	optimize "On"
	
	imgui_to_root = path.getrelative(os.getcwd(), root_directory)
	targetdir (imgui_to_root .. "/" .. target_location .. "/vendor/%{prj.name}")
	objdir (imgui_to_root .. "/" .. intermediate_location .. "/vendor/%{prj.name}")
	implibdir (imgui_to_root .. "/" .. intermediate_location .. "/vendor/%{prj.name}")

	files {
		"imgui/imconfig.h",
		"imgui/imgui.h",
		"imgui/imgui.cpp",
		"imgui/imgui_draw.cpp",
		"imgui/imgui_internal.h",
		"imgui/imgui_widgets.cpp",
		"imgui/imstb_rectpack.h",
		"imgui/imstb_textedit.h",
		"imgui/imstb_truetype.h",
	}

	includedirs {
		"imgui"
	}

	filter "configurations:Shipping"
		defines "IMGUI_DISABLE_METRICS_WINDOW"

	filter "system:windows"
		defines "WIN32_LEAN_AND_MEAN"

	filter "system:msc*"
		defines {
			-- "IMGUI_API=__declspec(dllexport)", -- if specified [kind "SharedLib"] for the GameEngineStudy
		}

	filter {}
