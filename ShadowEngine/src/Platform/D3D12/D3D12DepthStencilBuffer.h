#pragma once
#include "Common.h"
#include "D3D12SwapChain.h"

namespace ShadowEngine::Rendering::D3D12 {

	class D3D12DepthStencilBuffer
	{
		com_ptr<ID3D12Resource> depthStencilBuffer;
	public:
		D3D12DepthStencilBuffer(Ref<D3D12::D3D12DescriptorHeap> heap, Ref<D3D12::D3D12SwapChain> swap_chain);
	};

}
