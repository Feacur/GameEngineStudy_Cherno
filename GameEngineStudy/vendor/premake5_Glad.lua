project "Glad"
	kind "StaticLib"
	language "C"
	cdialect "C99"
	cppdialect "C++11"
	warnings "Default"
	removeflags { "FatalWarnings" }
	
	Glad_to_root = path.getrelative(os.getcwd(), root_directory)
	targetdir (Glad_to_root .. "/bin/" .. outputdir .. "/%{prj.name}")
	objdir (Glad_to_root .. "/bin-int/" .. outputdir .. "/%{prj.name}")

	files {
		"Glad/include/KHR/khrplatform.h",
		"Glad/include/glad/glad.h",
		"Glad/src/glad.c",
	}

	includedirs {
		"Glad/include"
	}
	
	filter "system:windows"
		staticruntime "Off"
		systemversion "latest"
