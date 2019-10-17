#include "shpch.h"
#include "D3D12CommandQueue.h"
#include "Common.h"
#include "D3D12RendererAPI.h"
#include "D3D12CommandList.h"

namespace ShadowEngine::Rendering::D3D12 {

	D3D12CommandQueue::D3D12CommandQueue()
	{
		D3D12_COMMAND_QUEUE_DESC commandQueueDesc;
		commandQueueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
		commandQueueDesc.Priority = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;
		commandQueueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
		commandQueueDesc.NodeMask = 0;

		DX_API("Failed to create command queue")
		D3D12RendererAPI::device->CreateCommandQueue(&commandQueueDesc, IID_PPV_ARGS(commandQueue.GetAddressOf()));
	}

	void D3D12CommandQueue::Execute(Ref<D3D12CommandList> commandList)
	{
		// Execute
		ID3D12CommandList* cLists[] = { commandList->GetCommandList().Get() };
		commandQueue->ExecuteCommandLists(_countof(cLists), cLists);
	}
	
	void D3D12CommandQueue::Signal(Ref<D3D12Fence> fence, uint64_t Value)
	{
		commandQueue->Signal(fence->GetFencePointer().Get(), Value);
	}
}
