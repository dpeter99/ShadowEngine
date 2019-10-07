#pragma once
#include "Common.h"

namespace  ShadowEngine::Rendering::D3D12 {

	class D3D12DescriptorHeap
	{
		com_ptr<ID3D12DescriptorHeap> _descriptorHeap;
	public:
		D3D12DescriptorHeap(D3D12_DESCRIPTOR_HEAP_FLAGS flags, D3D12_DESCRIPTOR_HEAP_TYPE type, UINT count);
		~D3D12DescriptorHeap();
		
		D3D12_CPU_DESCRIPTOR_HANDLE GetCPUDescriptorHandleForHeapStart();
	};

}