#include "shpch.h"
#include "D3D12DescriptorHeap.h"
#include "D3D12RendererAPI.h"

namespace  ShadowEngine::Rendering::D3D12 {

	D3D12DescriptorHeap::D3D12DescriptorHeap(D3D12_DESCRIPTOR_HEAP_FLAGS flags, D3D12_DESCRIPTOR_HEAP_TYPE type, UINT count)
	{
		D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc;
		rtvHeapDesc.Flags = flags;
		rtvHeapDesc.Type = type;
		rtvHeapDesc.NumDescriptors = count;
		rtvHeapDesc.NodeMask = 0;

		DX_API("Failed to create render target view descriptor heap")
			D3D12RendererAPI::device->CreateDescriptorHeap(&rtvHeapDesc, IID_PPV_ARGS(_descriptorHeap.GetAddressOf()));

		CPU_next_free = _descriptorHeap->GetCPUDescriptorHandleForHeapStart();
		GPU_next_free = _descriptorHeap->GetGPUDescriptorHandleForHeapStart();
		
		inc_size = D3D12RendererAPI::device->GetDescriptorHandleIncrementSize(type);
	}

	D3D12DescriptorHeap::~D3D12DescriptorHeap()
	{
		_descriptorHeap.Reset();
	}

	D3D12_CPU_DESCRIPTOR_HANDLE D3D12DescriptorHeap::GetCPUDescriptorHandleForHeapStart()
	{	
		return  _descriptorHeap->GetCPUDescriptorHandleForHeapStart();
	}

	DescriptorAllocation D3D12DescriptorHeap::Allocate(int count)
	{
		DescriptorAllocation res;
		
		res.CPU_TableStart = CPU_next_free;
		res.GPU_TableStart = GPU_next_free;
		res.incrementSize = inc_size;
		
		CPU_next_free = CPU_next_free.Offset(count , inc_size);
		GPU_next_free = GPU_next_free.Offset(count, inc_size);
		
		return res;
	}

	void D3D12DescriptorHeap::Reset()
	{
		_descriptorHeap.Reset();
	}
}
