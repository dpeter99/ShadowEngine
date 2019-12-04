#include "shpch.h"
#include "Texture.h"

#include "ShadowRenderer/Renderer.h"
#include "Platform/D3D12/D3D12Texture.h"

namespace ShadowEngine::Assets {

	Ref<Texture2DImpl> ShadowEngine::Assets::Texture2DImpl::Create(std::string path)
	{
		switch (ShadowEngine::Rendering::Renderer::GetAPI())
		{
		case Rendering::RendererAPI::API::None:    SH_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case Rendering::RendererAPI::API::D3D12:  return std::make_shared<Rendering::D3D12::D3D12Texture>(path);
		}

		SH_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}