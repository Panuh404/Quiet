workspace "Quiet"
	architecture "x86_64"
	startproject "Sandbox"
	
	configurations{
		"Debug",
		"Release",
		"Dist"
	}
	
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
	
--include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Quiet/vendor/GLFW/include"
IncludeDir["Glad"] = "Quiet/vendor/Glad/include"
IncludeDir["ImGui"] = "Quiet/vendor/ImGui"
IncludeDir["glm"] = "Quiet/vendor/glm"
IncludeDir["stb"] = "Quiet/vendor/stb"

include "Quiet/vendor/GLFW"
include "Quiet/vendor/Glad"
include "Quiet/vendor/ImGui"

project "Quiet"
	location "Quiet"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "Quiet_pch.h"
	pchsource "Quiet/src/Quiet_pch.cpp"

	files{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/stb/**h",
		"%{prj.name}/vendor/stb/**cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS",
		"GLFW_INCLUDE_NONE"
	}

	includedirs{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb}"
	}
	
	links{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines{
			"QUIET_PLATFORM_WINDOWS",
			"QUIET_BUILD_DLL"
		}

	filter "configurations:Debug"
		defines "QUIET_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "QUIET_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "QUIET_DIST"
		runtime "Release"
		optimize "on"


project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	files{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}
	
	includedirs{
		"Quiet/vendor/spdlog/include",
		"Quiet/src",
		"Quiet/vendor/",
		"%{IncludeDir.glm}"
	}
	
	links{
		"Quiet"
	}
	
	filter "system:windows"
		systemversion "latest"

		defines{
			"QUIET_PLATFORM_WINDOWS"
		}
		
	filter "configurations:Debug"
		defines "QUIET_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "QUIET_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "QUIET_DIST"
		runtime "Release" 
		optimize "on"