workspace "HasteLang"
    architecture "x86_64"

    configurations
    {
        "Debug",
        "Release",
    }

    flags
    {
        "MultiProcessorCompile",
    }

outputDir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "HasteLang"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"
    staticruntime "off"

    targetdir ("%{wks.location}/Build/bin/" .. outputDir)
    debugdir ("%{wks.location}/Build/bin/" .. outputDir)
    objdir ("%{wks.location}/Build/bin-int/" .. outputDir)

    files
    {
        "Source/**.cpp",
        "Source/**.hpp",
        "Source/**.c",
        "Source/**.h",
    }

    includedirs
    {
        "Source",
    }

    filter "configurations:Debug"
        defines "HL_DEBUG"
        runtime "Debug"
        symbols "on"
    
    filter "configurations:Release"
        defines "HL_RELEASE"
        runtime "Release"
        optimize "on"