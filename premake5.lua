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

include "ShadowEngine/dependencies/GLAD"
include "ShadowEngineBuild/dependencies"

project "ShadowEngine"
	location "ShadowEngine"
	kind "ConsoleApp"
	language "C++"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{IncludeDir.SDL2}",
		"%{IncludeDir.GLAD}"
	}

	links 
	{ 
		"SDL2",
		"SDL2main",
		"SDL2test",
		"Glad",
		"ShadowEngineBuild",
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"SE_WINDOWS"
		}

		libdirs {
			"%{prj.name}/dependencies/SDL2/lib/VC/%{cfg.architecture}/"
		}

		postbuildcommands{
			"{COPY} %{prj.location}/dependencies/SDL2/lib/VC/%{cfg.architecture}/SDL2.dll \"%{cfg.buildtarget.directory}\"",
			"{COPY} %{wks.location}/DemoGame \"%{cfg.buildtarget.directory}\""
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
	dotnetframework "4.6"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.cs",
	}

	links{
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
	kind "None"

	files{
		"%{prj.name}/**"
	}

	links{
		"ShadowEngineBuild"
	}

	prebuildcommands{
		"bin/"..outputdir.."/ShadowEngineBuild/ShadowEngineBuild.exe A %{prj.loaction}"
	}