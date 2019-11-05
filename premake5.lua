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
IncludeDir["assimp"] = "ShadowEngine/dependencies/assimp/include"

IncludeDir["ShadowEngine"] = "ShadowEngine/src"


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
		"%{prj.name}/src/**.hlsl",
		"%{prj.name}/src/**.hlsli",
		"%{prj.name}/dependencies/stb_image/**.h",
		"%{prj.name}/dependencies/stb_image/**.cpp",
		"%{prj.name}/dependencies/glm/glm/**.hpp",
		"%{prj.name}/dependencies/glm/glm/**.inl",
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS",
		"SH_ENABLE_ASSERTS"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{IncludeDir.SDL2}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}",
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.assimp}"
	}

	links 
	{ 
		"SDL2",
		"SDL2main",
		"SDL2test",
		"Glad",
		"ImGui",
		
		"ShadowEngineBuild",
		
		"opengl32.lib",
		"D3D12.lib",
		"DXGI.lib",
		"D3DCompiler.lib"
	}
	
	nuget { 
		"Assimp:3.0.0",
		"Assimp.redist:3.0.0"
	}

	local shader_dir = "../bin/" .. outputdir .. "/%{prj.name}/Shaders/"
	
	shadermodel "5.0"
	shaderentry "main"
	
	filter "files:**.hlsl"
		flags "ExcludeFromBuild"
		shaderobjectfileoutput (shader_dir .. "%{file.basename}.cso")
		shaderheaderfileoutput ("src/Shaders/%{file.basename}.h")
		
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
	
	links 
	{ 
		"ShadowEngine"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

