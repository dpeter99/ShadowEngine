project "ShadowEngine"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	debugdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")

	pchheader "shpch.h"
	pchsource "src/shpch.cpp"

	files
	{
		"src/**.h",
		"src/**.cpp",
		"src/**.cd",
		"src/**.hlsl",
		"src/**.hlsli",
		"dependencies/stb_image/**.h",
		"dependencies/stb_image/**.cpp",
		"dependencies/imgui/examples/imgui_impl_dx12.cpp",
		"dependencies/imgui/examples/imgui_impl_dx12.h"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS",
		"SH_ENABLE_ASSERTS"
	}

	includedirs
	{
		"src",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}",
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.assimp}",
		"dependencies/dxc/inc",
	}

	links 
	{ 
		"Glad",
		"ImGui",
		
		--"opengl32.lib",
		"D3D12.lib",
		"DXGI.lib",
		--"D3DCompiler.lib",
		"dependencies/dxc/lib/x64/dxcompiler.lib",
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
	
	shadermodel "6.0"
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
			"%{prj.name}/dependencies/SDL2/lib/VC/%{cfg.architecture}/",
			"%{prj.name}/dependencies/dxc/bin/%{cfg.architecture}/"
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