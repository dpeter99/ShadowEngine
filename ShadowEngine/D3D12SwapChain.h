#pragma once
#include "Platform/D3D12/Common.h"

namespace ShadowEngine::Rendering::D3D12 {

	class D3D12SwapChain
	{
		com_ptr<IDXGISwapChain3> swapChain{ nullptr };
	public:
		D3D12SwapChain(ShadowEngine::Ref<D3D12::D3D12CommandQueue> commandQueue);
	};

}