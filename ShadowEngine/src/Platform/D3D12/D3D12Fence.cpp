#include "shpch.h"
#include "D3D12Fence.h"
#include "DX12RendererAPI.h"

namespace ShadowEngine::Rendering::D3D12 {

	D3D12Fence::D3D12Fence()
	{
		DX_API("Failed to create fence")
		DX12RendererAPI::device->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(fence.GetAddressOf()));

		fenceEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
		if (fenceEvent == NULL) {
			DX_API("Failed to create windows event") HRESULT_FROM_WIN32(GetLastError());
		}
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

	void D3D12Fence::WaitForValue(uint64_t value, std::chrono::milliseconds duration)
	{
		if (fence->GetCompletedValue() < value)
		{
			DX_API("Failled to wait for fence")
			fence->SetEventOnCompletion(value, fenceEvent);
			::WaitForSingleObject(fenceEvent, static_cast<DWORD>(duration.count()));
		}
	}
}
