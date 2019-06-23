project "GLFW"
	kind "StaticLib"
	language "C"
	cdialect "C99"
	cppdialect "C++11"
	warnings "Default"
	removeflags { "FatalWarnings" }
	
	GLFW_to_root = path.getrelative(os.getcwd(), root_directory)
	targetdir (GLFW_to_root .. "/bin/" .. outputdir .. "/%{prj.name}")
	objdir (GLFW_to_root .. "/bin-int/" .. outputdir .. "/%{prj.name}")

	files {
		"GLFW/include/GLFW/glfw3.h",
		"GLFW/include/GLFW/glfw3native.h",
		"GLFW/src/glfw_config.h",
		"GLFW/src/context.c",
		"GLFW/src/init.c",
		"GLFW/src/input.c",
		"GLFW/src/monitor.c",
		"GLFW/src/vulkan.c",
		"GLFW/src/window.c"
	}

	includedirs {
		"GLFW/include"
	}
	
	filter "system:windows"
		staticruntime "Off"
		systemversion "latest"
		
		files {
			"GLFW/src/win32_init.c",
			"GLFW/src/win32_joystick.c",
			"GLFW/src/win32_monitor.c",
			"GLFW/src/win32_time.c",
			"GLFW/src/win32_thread.c",
			"GLFW/src/win32_window.c",
			"GLFW/src/wgl_context.c",
			"GLFW/src/egl_context.c",
			"GLFW/src/osmesa_context.c"
		}

		defines {
			"_GLFW_WIN32",
			"_CRT_SECURE_NO_WARNINGS"
		}

		links {
			"gdi32",
		}
