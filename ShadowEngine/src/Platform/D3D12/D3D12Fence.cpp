#include "shpch.h"
#include "D3D12Fence.h"
#include "D3D12RendererAPI.h"

namespace ShadowEngine::Rendering::D3D12 {

	D3D12Fence::D3D12Fence()
	{
		DX_API("Failed to create fence")
		D3D12RendererAPI::device->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(fence.GetAddressOf()));
	}
}
