workspace "ShadowEngine"
	architecture "x64"
	startproject "ShadowEngine"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}
	
	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["SDL2"] = "ShadowEngine/dependencies/SDL2/include"
IncludeDir["Glad"] = "ShadowEngine/dependencies/Glad/include"
IncludeDir["ImGui"] = "ShadowEngine/dependencies/imgui"
IncludeDir["glm"] = "ShadowEngine/dependencies/glm"
IncludeDir["stb_image"] = "ShadowEngine/dependencies/stb_image"
IncludeDir["spdlog"] = "ShadowEngine/dependencies/spdlog/include"


group "Dependencies"
	include "ShadowEngine/dependencies/Glad"
	include "ShadowEngine/dependencies/imgui"
	
	include "ShadowEngineBuild/dependencies/TiledSharp"

group ""

project "ShadowEngine"
	location "ShadowEngine"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
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
		"%{prj.name}/src/**.cd",
		"%{prj.name}/dependencies/stb_image/**.h",
		"%{prj.name}/dependencies/stb_image/**.cpp",
		"%{prj.name}/dependencies/glm/glm/**.hpp",
		"%{prj.name}/dependencies/glm/glm/**.inl",
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{IncludeDir.SDL2}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}",
		"%{IncludeDir.spdlog}"
	}

	links 
	{ 
		"SDL2",
		"SDL2main",
		"SDL2test",
		"Glad",
		"ImGui",
		"ShadowEngineBuild",
		"opengl32.lib"
	}

	filter "system:windows"
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
		defines "SE_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "SE_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "SE_DIST"
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

externalproject "ShadowEngineBuild"
   location "ShadowEngineBuild"
   uuid "D11098AF-3D27-9645-869E-2167F2F366CD"
   kind "ConsoleApp"
   language "C#"



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

