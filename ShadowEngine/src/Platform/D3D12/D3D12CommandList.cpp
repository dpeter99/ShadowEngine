#include "shpch.h"
#include "D3D12CommandList.h"
#include "D3D12RendererAPI.h"

namespace ShadowEngine::Rendering::D3D12 {
	D3D12CommandList::D3D12CommandList()
	{
		DX_API("Failed to create command allocator")
		D3D12RendererAPI::device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(commandAllocator.GetAddressOf()));

		DX_API("Failed to greate graphics command list")
		D3D12RendererAPI::device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, commandAllocator.Get(), nullptr, IID_PPV_ARGS(commandList.GetAddressOf()));
	}

	void D3D12CommandList::Reset()
	{
		commandAllocator->Reset();
		commandList->Reset(commandAllocator.Get(), nullptr);
	}
	
}
