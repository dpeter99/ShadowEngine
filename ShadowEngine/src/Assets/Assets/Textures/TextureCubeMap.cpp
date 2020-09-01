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

	TextureCubeMap::TextureCubeMap()
	{

	}

	void TextureCubeMap::Load(SFF::SFFElement& root, FileSystem::Path path)
	{
		auto* cubemap_root = root.GetChildByName("Shader");
		up_texture = path.GetFullPath() + cubemap_root->GetStringProperty("up");
	}

	uint32_t TextureCubeMap::GetWidth() const
	{
		return uint32_t();
	}

	uint32_t TextureCubeMap::GetHeight() const
	{
		return uint32_t();
	}

	uint32_t TextureCubeMap::GetZ() const
	{
		return uint32_t();
	}

	
}
