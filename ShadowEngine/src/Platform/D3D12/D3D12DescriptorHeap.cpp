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
	}

	D3D12DescriptorHeap::~D3D12DescriptorHeap()
	{
		_descriptorHeap.Reset();
	}

	D3D12_CPU_DESCRIPTOR_HANDLE D3D12DescriptorHeap::GetCPUDescriptorHandleForHeapStart()
	{
		return  _descriptorHeap->GetCPUDescriptorHandleForHeapStart();
	}
}
