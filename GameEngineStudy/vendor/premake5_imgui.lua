project "imgui"
	kind "StaticLib"
	language "C"
	cdialect "C99"
	cppdialect "C++11"
	warnings "Default"
	removeflags { "FatalWarnings" }
	
	imgui_to_root = path.getrelative(os.getcwd(), root_directory)
	targetdir (imgui_to_root .. "/bin/" .. outputdir .. "/%{prj.name}")
	objdir (imgui_to_root .. "/bin-int/" .. outputdir .. "/%{prj.name}")

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
		"imgui/imgui_demo.cpp",
	}

	includedirs {
		"imgui"
	}
	
	filter "system:windows"
		staticruntime "Off"
		systemversion "latest"
		
		defines {
			"IMGUI_API=__declspec(dllexport)", -- if specified [kind "SharedLib"] for the GameEngineStudy
		}
