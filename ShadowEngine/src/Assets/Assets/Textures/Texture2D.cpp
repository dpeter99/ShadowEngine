#include "shpch.h"
#include "Texture2D.h"


#include "Platform/D3D12/Textures/D3D12Texture2D.h"
#include "ShadowRenderer/Renderer.h"

namespace ShadowEngine::Assets {

	Ref<Texture2DImpl> Texture2DImpl::Create(Texture2D* asset)
	{
		switch (ShadowEngine::Rendering::Renderer::GetAPI())
		{
		case Rendering::RendererAPI::API::None:    SH_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case Rendering::RendererAPI::API::D3D12:  return std::make_shared<Rendering::D3D12::D3D12Texture2D>(asset);
		}

		SH_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	Texture2D::Texture2D(std::string path) : Texture(path)
	{
		impl = Texture2DImpl::Create(this);
	}

	Texture2D::Texture2D()
	{
		impl = Texture2DImpl::Create(this);
	}

	std::string Texture2D::GetTexturePath()
	{
		return texture;
	}

	void Texture2D::Load(SFF::SFFElement& root, FileSystem::Path path)
	{
		ShadowAsset::Load(root, path);

		auto* tex_root = root.GetChildByName("Texture");

		texture = path.GetFullFolderPath() + tex_root->GetStringProperty("texture");

		impl->Load();
	}

	uint32_t Texture2D::GetWidth() const
	{
		//TODO: Return the actual height
		return 0;
	}

	uint32_t Texture2D::GetHeight() const
	{
		//TODO: Return the actual height
		return 0;
	}

	uint32_t Texture2D::GetZ() const
	{
		return 0;
	}
}
