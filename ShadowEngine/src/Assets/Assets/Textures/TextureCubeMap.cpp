#include "shpch.h"
#include "TextureCubeMap.h"
#include "Platform/D3D12/Textures/D3D12Texture2D.h"
#include "ShadowRenderer/Renderer.h"
#include "Platform/D3D12/Textures/D3D12TextureCubeMap.h"

namespace ShadowEngine::Assets {

	Ref<TextureCubeMapImpl> TextureCubeMapImpl::Create(TextureCubeMap* asset)
	{
		switch (Rendering::Renderer::GetAPI())
		{
		case Rendering::RendererAPI::API::None:    SH_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case Rendering::RendererAPI::API::D3D12:  return std::make_shared<Rendering::D3D12::D3D12TextureCubeMap>(asset);
		}

		SH_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	TextureCubeMap::TextureCubeMap() : Texture()
	{
		impl = TextureCubeMapImpl::Create(this);
	}

	std::string TextureCubeMap::GetTexturePath(int i)
	{
		switch (i) {
		case 0:
			return front_texture;
			break;
		case 1:
			return back_texture;
			break;
		case 2:
			return up_texture;
			break;
		case 3:
			return down_texture;
			break;
		case 4:
			return right_texture;
			break;
		case 5:
			return left_texture;
			break;
		}
	}

	void TextureCubeMap::Load(SFF::SFFElement& root, FileSystem::Path path)
	{
		auto* cubemap_root = root.GetChildByName("CubeMap");
		up_texture = path.GetFullPath() + cubemap_root->GetStringProperty("up");
		down_texture = path.GetFullPath() + cubemap_root->GetStringProperty("down");
		front_texture = path.GetFullPath() + cubemap_root->GetStringProperty("front");
		back_texture = path.GetFullPath() + cubemap_root->GetStringProperty("back");
		left_texture = path.GetFullPath() + cubemap_root->GetStringProperty("left");
		right_texture = path.GetFullPath() + cubemap_root->GetStringProperty("right");

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
		return 6;
	}

	
}
