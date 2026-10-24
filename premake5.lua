if _ACTION == "clean" then
    os.rmdir("build")
    os.rmdir(".vs")
    os.remove(os.matchfiles("**.sln*"))
    os.remove(os.matchfiles("**.vcxproj*"))
end

workspace "NicheKiller"
    characterset "Unicode"
    architecture "x64"
    configurations { "Debug", "Release" }
    startproject "NicheKiller"

project "NicheKiller"
    kind "WindowedApp"
    language "C++"
    cppdialect "C++26"
    -- staticruntime "off"

    targetdir ("%{wks.location}/build/bin/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}")
    objdir ("%{wks.location}/build/obj/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/%{prj.name}")

    files
    {
       "src/**.hpp",
       "src/**.cpp",
    }

    includedirs
    {
	
    }


    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        runtime "Release"
        optimize "on"