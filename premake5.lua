workspace "GameEngineStudy"
    architecture "x64"

    configurations
    {
        "Debug",
        "Development",
        "Shipping"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
enginename = "GameEngineStudy"

project "GameEngineStudy"
    location "GameEngineStudy"
    kind "SharedLib"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "%{prj.name}/vendor/spdlog/include"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "GES_PLATFORM_WINDOWS",
            "GES_BUILD_DLL"
        }

        postbuildcommands
        {
            ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
        }

    filter "configurations:Debug"
        defines "GES_DEBUG"
        symbols "On"

    filter "configurations:Development"
        defines "GES_DEVELOPMENT"
        optimize "On"

    filter "configurations:Shipping"
        defines "GES_SHIPPING"
        optimize "On"

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        enginename .. "/src",
        enginename .. "/vendor/spdlog/include"
    }

    links
    {
        "GameEngineStudy"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "GES_PLATFORM_WINDOWS"
        }

    filter "configurations:Debug"
        defines "GES_DEBUG"
        symbols "On"

    filter "configurations:Development"
        defines "GES_DEVELOPMENT"
        optimize "On"

    filter "configurations:Shipping"
        defines "GES_SHIPPING"
        optimize "On"
