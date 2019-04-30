workspace "ShadowEngine"
	architecture "x64"
	startproject "ShadowEngine"



	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}



outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["SDL2"] = "ShadowEngine/dependencies/SDL2/include"
IncludeDir["GLAD"] = "ShadowEngine/dependencies/GLAD/include"
IncludeDir["ImGui"] = "ShadowEngine/dependencies/imgui"

include "ShadowEngine/dependencies/GLAD"
include "ShadowEngine/dependencies/IMGUI"
include "ShadowEngineBuild/dependencies/TiledSharp"


project "ShadowEngine"
	location "ShadowEngine"
	kind "ConsoleApp"
	language "C++"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	debugdir ("bin/" .. outputdir .. "/%{prj.name}")

	pchheader "shpch.h"
	pchsource "ShadowEngine/src/shpch.cpp"


	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/src/**.cd"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{IncludeDir.SDL2}",
		"%{IncludeDir.GLAD}",
		"%{IncludeDir.ImGui}"
	}

	links 
	{ 
		"SDL2",
		"SDL2main",
		"SDL2test",
		"Glad",
		"ImGui",
		"ShadowEngineBuild",
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines{
			"SE_WINDOWS"
		}

		libdirs {
			"%{prj.name}/dependencies/SDL2/lib/VC/%{cfg.architecture}/"
		}

		postbuildcommands{
			"{COPY} %{prj.location}/dependencies/SDL2/lib/VC/%{cfg.architecture}/SDL2.dll \"%{cfg.buildtarget.directory}\"",
			"{COPY} %{wks.location}/DemoGame/Resources \"%{cfg.buildtarget.directory}/Resources\""
		}

	filter "configurations:Debug"
		defines "HZ_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "HZ_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "HZ_DIST"
		runtime "Release"
		optimize "On"





project "ShadowEngineBuild"
	location "ShadowEngineBuild"
	kind "ConsoleApp"
	language "C#"
	

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.cs",
	}

	links{
		"System.Xml.Linq",
		"TiledSharp",
	}
	

	excludes { "**/bin/**", "**/obj/**" } 

	includedirs
	{
		"%{prj.name}",
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"SE_WINDOWS"
		}

	filter "configurations:Debug"
		defines "HZ_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "HZ_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "HZ_DIST"
		runtime "Release"
		optimize "On"


project "DemoGame"
	location "DemoGame"
	kind "Utility"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files{
		"%{prj.name}/Resources/**"
	}

	links{
		"ShadowEngineBuild"
	}

	prebuildcommands{
		"%{wks.location}bin/"..outputdir.."/ShadowEngineBuild/ShadowEngineBuild.exe A %{prj.location}/Resources ",
		--"echo %{prj.location}"
	}

project "Planning"
	location "Planning"
	kind "ConsoleApp"
	language "C++"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	debugdir ("bin/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}

	includedirs
	{
		"%{prj.name}/src",
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

