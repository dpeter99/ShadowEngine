#include "shpch.h"
#include "SwapChain.h"
#include "Renderer.h"
#include "Platform/D3D12/D3D12SwapChain.h"

namespace ShadowEngine::Rendering {
	Ref<SwapChain> SwapChain::Create(Ref<CommandQueue> commandQueue)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    SH_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		//case RendererAPI::API::D3D12:   return std::make_shared<D3D12::D3D12SwapChain>(std::dynamic_pointer_cast<D3D12::D3D12CommandQueue>(commandQueue));
		}
		
		
		SH_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}
