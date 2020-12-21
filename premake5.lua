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
IncludeDir["Glad"] = "%{wks.location}/ShadowEngine/dependencies/Glad/include"
IncludeDir["ImGui"] = "%{wks.location}/ShadowEngine/dependencies/imgui"
IncludeDir["glm"] = "%{wks.location}/ShadowEngine/dependencies/glm"
IncludeDir["stb_image"] = "%{wks.location}/ShadowEngine/dependencies/stb_image"
IncludeDir["spdlog"] = "%{wks.location}/ShadowEngine/dependencies/spdlog/include"
IncludeDir["assimp"] = "%{wks.location}/ShadowEngine/dependencies/assimp/include"
IncludeDir["DXC"] = "%{wks.location}/ShadowEngine/dependencies/dxc/inc"

IncludeDir["ShadowEngine"] = "ShadowEngine/src"


group "Dependencies"
	include "ShadowEngine/dependencies/Glad"
	include "ShadowEngine/dependencies/imgui"
	
	externalproject "TiledSharp"
	   location "ShadowEngineBuild/dependencies/TiledSharp/TiledSharp"
	   uuid "75220C4A-61DA-4D97-CAE1-26F3B6B8E887"
	   kind "SharedLib"
	   language "C#"

project "Glm"
	location "ShadowEngine/dependencies/glm"
	kind "None"
	language "C++"
	cppdialect "C++17"

	files
    {
        "ShadowEngine/dependencies/glm/glm/**.hpp",
		"ShadowEngine/dependencies/glm/glm/**.inl",
    }

group ""


include "ShadowEngine"

include "ShadowLight"


project "DemoGame"
	location "DemoGame"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	debugdir ("bin/" .. outputdir .. "/%{prj.name}")

	files{
		"%{prj.name}/Resources/**",
		"%{prj.name}/src/**"
	}

	links
	{
		--"ShadowEngineBuild",
		"ShadowEngine"
	}

	includedirs{
		"ShadowEngine/src",
		"ShadowEngine/dependencies",
		"%{IncludeDir.glm}",
		"%{IncludeDir.spdlog}",
	}

	prebuildcommands{
		"%{wks.location}bin/"..outputdir.."/ShadowEngineBuild/ShadowEngineBuild.exe A %{prj.location}/Resources ",
		--"echo %{prj.location}"
		--"{COPY} %{prj.location}/dependencies/SDL2/lib/VC/%{cfg.architecture}/SDL2.dll \"%{cfg.buildtarget.directory}\"",
		"{COPY} %{wks.location}/DemoGame/Resources \"%{cfg.buildtarget.directory}/Resources\"",
		"{COPY} %{cfg.buildtarget.directory}/../ShadowEngine/Shaders \"%{cfg.buildtarget.directory}/Shaders\""
	}

	nuget { 
		"Assimp:3.0.0",
		"Assimp.redist:3.0.0",
		"sdl2.nuget:2.0.10",
		"sdl2.nuget.redist:2.0.10",
		"sdl2_image.nuget:2.0.5",
		"sdl2_image.nuget.redist:2.0.5"
	}

	filter "system:windows"
		systemversion "latest"
		
	filter "configurations:Debug"
		defines "HZ_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "HZ_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "HZ_DIST"
		runtime "Release"
		optimize "on"






externalproject "ShadowEngineBuild"
   location "ShadowEngineBuild"
   uuid "9A19103F-16F7-4668-BE54-9A1E7A4F7556"
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
	
	links 
	{ 
		"ShadowEngine"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

