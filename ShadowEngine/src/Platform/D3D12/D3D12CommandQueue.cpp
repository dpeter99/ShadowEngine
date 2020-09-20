#include "shpch.h"
#include "D3D12CommandQueue.h"
#include "Common.h"
#include "DX12RendererAPI.h"
#include "CommandList.h"

namespace ShadowEngine::Rendering::D3D12 {

	D3D12CommandQueue::D3D12CommandQueue(D3D12_COMMAND_LIST_TYPE type)
	{
		D3D12_COMMAND_QUEUE_DESC commandQueueDesc;
		commandQueueDesc.Type = type;
		commandQueueDesc.Priority = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;
		commandQueueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
		commandQueueDesc.NodeMask = 0;

		DX_API("Failed to create command queue")
		DX12RendererAPI::device->CreateCommandQueue(&commandQueueDesc, IID_PPV_ARGS(commandQueue.GetAddressOf()));
	}

	void D3D12CommandQueue::SetName(std::wstring name)
	{
		commandQueue->SetName(name.c_str());
		fence.GetFencePointer()->SetName((name + L"_Fence").c_str());
	}

	void D3D12CommandQueue::Execute(Ref<CommandList> commandList)
	{
		// Execute
		ID3D12CommandList* cLists[] = { commandList->GetCommandList().Get() };
		commandQueue->ExecuteCommandLists(_countof(cLists), cLists);
	}
	
	uint64_t D3D12CommandQueue::Signal()
	{
		uint64_t fenceValue = fence_value;
		fence_value += 1;
		commandQueue->Signal(fence.GetFencePointer().Get(), fenceValue);
		return fenceValue;
	}

	uint64_t D3D12CommandQueue::GetNextSignalValue()
	{
		return fence_value + 1;
	}

	void D3D12CommandQueue::WaitForFenceValue(uint64_t value)
	{
		fence.WaitForValue(value);
	}

	uint64_t D3D12CommandQueue::GetCompletedValue()
	{
		return fence.GetCompletedValue();
	}
}
