#include "shpch.h"
#include "D3D12Fence.h"
#include "DX12RendererAPI.h"

namespace ShadowEngine::Rendering::D3D12 {

	D3D12Fence::D3D12Fence()
	{
		DX_API("Failed to create fence")
		DX12RendererAPI::device->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(fence.GetAddressOf()));
	}
	UINT64 D3D12Fence::GetCompletedValue()
	{
		return fence->GetCompletedValue();
	}
	void D3D12Fence::SetEventOnCompletion(const UINT64 fv, HANDLE fenceEvent)
	{
		DX_API("Failed to sign up for event completion")
		fence->SetEventOnCompletion(fv, fenceEvent);
	}
}
