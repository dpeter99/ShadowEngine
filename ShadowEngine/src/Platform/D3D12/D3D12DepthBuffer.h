#pragma once
#include "Platform/D3D12/Common.h"

namespace ShadowEngine::Rendering::D3D12 {

	class D3D12DepthBuffer
	{
		com_ptr<ID3D12Resource> depthStencilBuffer;
		com_ptr<ID3D12DescriptorHeap> descriptorHeap;
	public:
		D3D12DepthBuffer(D3D12_RECT scissorRect);

		CD3DX12_CPU_DESCRIPTOR_HANDLE GetDescriptorHandle();
	};

}