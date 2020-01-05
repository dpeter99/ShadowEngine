#include "shpch.h"
#include "TextureCubeMap.h"
#include "Platform/D3D12/Textures/D3D12Texture2D.h"
#include "ShadowRenderer/Renderer.h"
#include "Platform/D3D12/Textures/D3D12TextureCubeMap.h"

namespace ShadowEngine::Assets {

	Ref<TextureCubeMapImpl> TextureCubeMapImpl::Create(std::string path)
	{
		switch (Rendering::Renderer::GetAPI())
		{
		case Rendering::RendererAPI::API::None:    SH_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case Rendering::RendererAPI::API::D3D12:  return std::make_shared<Rendering::D3D12::D3D12TextureCubeMap>(path);
		}

		SH_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	TextureCubeMap::TextureCubeMap(const std::string& path) : Texture(path)
	{
		impl = TextureCubeMapImpl::Create(path);
	}

	
}
