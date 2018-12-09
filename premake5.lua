workspace "GameEngineStudy"
    architecture "x64"
    startproject "Sandbox"
    warnings "Extra"
    flags { "FatalWarnings", "NoMinimalRebuild" }
    floatingpoint "Fast"
    floatingpointexceptions "off"

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
        }

    filter "toolset:gcc*"
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

project "GameEngineStudy"
    location "GameEngineStudy"
    kind "SharedLib"
    language "C++"

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
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        defines {
            "GES_PLATFORM_WINDOWS",
            "GES_BUILD_DLL",
        }

        postbuildcommands {
            ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
        }

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"

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
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        defines {
            "GES_PLATFORM_WINDOWS",
        }
