workspace "Quiet"
    architecture "x64"

    configurations{
		"Debug",
		"Release",
		"Dist"
    }
	
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
	
-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Quiet/Dependencies/GLFW/include"
	
include "Quiet/Dependencies/GLFW"
	
project "Quiet"
	location "Quiet"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "Quiet_pch.h"
	pchsource "Quiet/src/Quiet_pch.cpp"

	files{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs{
		"%{prj.name}/src",
		"%{prj.name}/Dependencies/spdlog/include",
		"%{IncludeDir.GLFW}"
	}
	
	links{
		"GLFW",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines{
			"QUIET_PLATFORM_WINDOWS",
			"QUIET_BUILD_DLL",
            "GLFW_INCLUDE_NONE"
		}
		
		postbuildcommands{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

    filter "configurations:Debug"
        defines "QUIET_DEBUG"
        buildoptions "/MDd"
        symbols "On"

    filter "configurations:Release"
        defines "QUIET_RELEASE"
        buildoptions "/MD"
        optimize "On"

    filter "configurations:Dist"
        defines "QUIET_DIST"
        buildoptions "/MD"
        optimize "On"

    
project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	files{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}
	
	includedirs{
		"Quiet/Dependencies/spdlog/include",
		"Quiet/src"
	}
	
	links{
		"Quiet"
	}
	
	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines{
			"QUIET_PLATFORM_WINDOWS"
		}
		
		filter "configurations:Debug"
			defines "QUIET_DEBUG"
			buildoptions "/MDd"
			symbols "On"

		filter "configurations:Release"
			defines "QUIET_RELEASE"
			buildoptions "/MD"
			optimize "On"

		filter "configurations:Dist"
			defines "QUIET_DIST"
			buildoptions "/MD"
			optimize "On"
			