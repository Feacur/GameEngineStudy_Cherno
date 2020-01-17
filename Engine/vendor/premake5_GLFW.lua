project "GLFW"
	kind "StaticLib"
	language "C"
	cdialect "C99"
	cppdialect "C++11"
	characterset ("Unicode") -- Default, Unicode, MBCS, ASCII
	warnings "Default"
	removeflags { "FatalWarnings" }
	
	symbols "Off"
	optimize "On"
	
	GLFW_to_root = path.getrelative(os.getcwd(), root_directory)
	targetdir (GLFW_to_root .. "/" .. target_location .. "/vendor/%{prj.name}")
	objdir (GLFW_to_root .. "/" .. intermediate_location .. "/vendor/%{prj.name}")
	implibdir (GLFW_to_root .. "/" .. intermediate_location .. "/vendor/%{prj.name}")

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
		files {
			"GLFW/src/win32_init.c",
			"GLFW/src/win32_joystick.c",
			"GLFW/src/win32_monitor.c",
			"GLFW/src/win32_time.c",
			"GLFW/src/win32_thread.c",
			"GLFW/src/win32_window.c",
			"GLFW/src/wgl_context.c",
			"GLFW/src/egl_context.c",
			"GLFW/src/osmesa_context.c",
		}
		defines {
			"_GLFW_WIN32",
			"WIN32_LEAN_AND_MEAN",
			"_GLFW_USE_HYBRID_HPG",
			-- "_GLFW_USE_OPTIMUS_HPG",
			-- "_CRT_SECURE_NO_WARNINGS",
		}

	filter "system:linux"
		pic "On"
		files {
			"src/x11_init.c",
			"src/x11_monitor.c",
			"src/x11_window.c",
			"src/xkb_unicode.c",
			"src/posix_time.c",
			"src/posix_thread.c",
			"src/glx_context.c",
			"src/egl_context.c",
			"src/osmesa_context.c",
			"src/linux_joystick.c",
		}
		defines {
			"_GLFW_X11",
		}

	filter {}
