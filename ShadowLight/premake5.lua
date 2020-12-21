project "ShadowLight"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	debugdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")

	files{
		"Resources/**",
		"src/**"
	}

	links
	{
		"ImGui",
		--"ShadowEngineBuild",
		"ShadowEngine"
	}

	includedirs{
		"%{wks.location}/ShadowEngine/src",
		"%{wks.location}/ShadowEngine/dependencies",
		"%{IncludeDir.glm}",
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.DXC}"
	}

	prebuildcommands{
		[[
			%{wks.location}/bin/]] .. outputdir .. [[/ShadowEngineBuild/net5.0/ShadowEngineBuild.exe --asset-root %{prj.location}/Resources --output %{wks.location}/bin/]] .. outputdir .. [[/%{prj.name}
		]],
		--"echo %{prj.location}"
		--"{COPY} %{prj.location}/dependencies/SDL2/lib/VC/%{cfg.architecture}/SDL2.dll \"%{cfg.buildtarget.directory}\"",
		--"{COPY} %{wks.location}/ShadowLight/Resources \"%{cfg.buildtarget.directory}/Resources\"",
		--"{COPY} %{cfg.buildtarget.directory}/../ShadowEngine/Shaders \"%{cfg.buildtarget.directory}/Shaders\""
	}

	nuget { 
		"Assimp:3.0.0",
		"Assimp.redist:3.0.0",
		"sdl2.nuget:2.0.10",
		"sdl2.nuget.redist:2.0.10",
		"sdl2_image.nuget:2.0.5",
		"sdl2_image.nuget.redist:2.0.5"
	}

	local shader_dir = "../bin/" .. outputdir .. "/%{prj.name}/"
	
	shadermodel "6.3"
	shaderentry "main"

	filter "files:**.hlsl"
		flags "ExcludeFromBuild"
		shaderobjectfileoutput (shader_dir .. [[/%%(RelativeDir)%%(Filename).cso]])
		
	filter "files:**-FS.hlsl"
		removeflags "ExcludeFromBuild"
		shadertype "Pixel"
		
	filter "files:**-VS.hlsl"
		removeflags "ExcludeFromBuild"
		shadertype "Vertex"


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