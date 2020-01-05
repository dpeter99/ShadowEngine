#include "shpch.h"
#include "CommandQueue.h"
#include "RendererAPI.h"
#include "Platform/D3D12/D3D12CommandQueue.h"

namespace ShadowEngine::Rendering {

	std::shared_ptr<CommandQueue> CommandQueue::Create()
	{
		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::API::None:    SH_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		//case RendererAPI::API::D3D12:   return std::make_shared<D3D12::D3D12CommandQueue>();
		}

		SH_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}
