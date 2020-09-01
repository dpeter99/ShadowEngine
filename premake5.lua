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
IncludeDir["Glad"] = "ShadowEngine/dependencies/Glad/include"
IncludeDir["ImGui"] = "ShadowEngine/dependencies/imgui"
IncludeDir["glm"] = "ShadowEngine/dependencies/glm"
IncludeDir["stb_image"] = "ShadowEngine/dependencies/stb_image"
IncludeDir["spdlog"] = "ShadowEngine/dependencies/spdlog/include"
IncludeDir["assimp"] = "ShadowEngine/dependencies/assimp/include"

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

project "ShadowEngine"
	location "ShadowEngine"
	kind "StaticLib"
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
		"%{prj.name}/src/**.hlsl",
		"%{prj.name}/src/**.hlsli",
		"%{prj.name}/dependencies/stb_image/**.h",
		"%{prj.name}/dependencies/stb_image/**.cpp",
		"%{prj.name}/dependencies/imgui/examples/imgui_impl_dx12.cpp",
		"%{prj.name}/dependencies/imgui/examples/imgui_impl_dx12.h"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS",
		"SH_ENABLE_ASSERTS"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}",
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.assimp}"
	}

	links 
	{ 
		"Glad",
		"ImGui",
		
		"opengl32.lib",
		"D3D12.lib",
		"DXGI.lib",
		"D3DCompiler.lib",
		"dxguid.lib"
	}
	
	dependson 
	{
		"ShadowEngineBuild"
	}
	
	nuget { 
		"Assimp:3.0.0",
		"Assimp.redist:3.0.0",
		"sdl2.nuget:2.0.10",
		"sdl2.nuget.redist:2.0.10",
		"sdl2_image.nuget:2.0.5",
		"sdl2_image.nuget.redist:2.0.5"
	}

	local shader_dir = "../bin/" .. outputdir .. "/%{prj.name}/Shaders/"
	
	shadermodel "5.0"
	shaderentry "main"
	
	filter "files:ShadowEngine/dependencies/**.cpp"
		flags "NoPCH"

	filter "files:**.hlsl"
		flags "ExcludeFromBuild"
		shaderobjectfileoutput (shader_dir .. "%{file.basename}.cso")
		
	filter "files:**-FS.hlsl"
		removeflags "ExcludeFromBuild"
		shadertype "Pixel"
		
	filter "files:**-VS.hlsl"
		removeflags "ExcludeFromBuild"
		shadertype "Vertex"

	filter "system:windows"
		systemversion "latest"

		defines{
			"SE_WINDOWS"
		}

		libdirs {
			"%{prj.name}/dependencies/SDL2/lib/VC/%{cfg.architecture}/"
		}

		postbuildcommands{
			--"{COPY} %{prj.location}/dependencies/SDL2/lib/VC/%{cfg.architecture}/SDL2.dll \"%{cfg.buildtarget.directory}\"",
			--"{COPY} %{wks.location}/DemoGame/Resources \"%{cfg.buildtarget.directory}/Resources\""
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


project "ShadowLight"
	location "ShadowLight"
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
		"ImGui",
		--"ShadowEngineBuild",
		"ShadowEngine"
	}

	includedirs{
		"ShadowEngine/src",
		"ShadowEngine/dependencies",
		"%{IncludeDir.glm}",
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.ImGui}"
	}

	prebuildcommands{
		"%{wks.location}bin/"..outputdir.."/ShadowEngineBuild/netcoreapp3.1/ShadowEngineBuild.exe A %{prj.location}/Resources ",
		--"echo %{prj.location}"
		--"{COPY} %{prj.location}/dependencies/SDL2/lib/VC/%{cfg.architecture}/SDL2.dll \"%{cfg.buildtarget.directory}\"",
		"{COPY} %{wks.location}/ShadowLight/Resources \"%{cfg.buildtarget.directory}/Resources\"",
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

