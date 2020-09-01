#include "shpch.h"
#include "Texture.h"

#include "ShadowRenderer/Renderer.h"
#include "Platform/D3D12/Textures/D3D12Texture2D.h"

namespace ShadowEngine::Assets {

	Texture::Texture(std::string path)
	{
	}

	Texture::Texture()
	{
	}

	Ref<Texture2DImpl> ShadowEngine::Assets::Texture2DImpl::Create(std::string path)
	{
		switch (ShadowEngine::Rendering::Renderer::GetAPI())
		{
		case Rendering::RendererAPI::API::None:    SH_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case Rendering::RendererAPI::API::D3D12:  return std::make_shared<Rendering::D3D12::D3D12Texture2D>(path);
		}

		SH_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	ShadowEngine::Assets::Texture2D::Texture2D(std::string path) : Texture(path)
	{
		impl = Texture2DImpl::Create(path);
	}



}
