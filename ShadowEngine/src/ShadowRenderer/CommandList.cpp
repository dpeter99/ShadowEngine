#include "shpch.h"
#include "CommandList.h"
#include "RendererAPI.h"
//#include "Platform/D3D12/D3D12CommandList.h"

namespace ShadowEngine::Rendering {
	/*
	std::shared_ptr<CommandList> CommandList::Create()
	{
		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::API::None:    SH_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		//case RendererAPI::API::D3D12: return std::make_shared <D3D12::CommandList>();
		}

		SH_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
	*/
}
