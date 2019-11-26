#pragma once
#include "Common.h"

namespace  ShadowEngine::Rendering::D3D12 {

	struct DescriptorAllocation
	{
		CD3DX12_CPU_DESCRIPTOR_HANDLE CPU_TableStart;
		CD3DX12_GPU_DESCRIPTOR_HANDLE GPU_TableStart;

		UINT incrementSize;
		
		DescriptorAllocation operator[](int i)
		{
			DescriptorAllocation res = *this;
			res.Offset(i);
			return res;
		}

		void Offset(int count)
		{
			CPU_TableStart = CPU_TableStart.Offset(count, incrementSize);
			GPU_TableStart = GPU_TableStart.Offset(count, incrementSize);
		}
		
	};
	
	class D3D12DescriptorHeap
	{
		com_ptr<ID3D12DescriptorHeap> _descriptorHeap;

		CD3DX12_CPU_DESCRIPTOR_HANDLE  CPU_next_free;
		CD3DX12_GPU_DESCRIPTOR_HANDLE  GPU_next_free;
		UINT inc_size;
	public:
		D3D12DescriptorHeap(D3D12_DESCRIPTOR_HEAP_FLAGS flags, D3D12_DESCRIPTOR_HEAP_TYPE type, UINT count);
		~D3D12DescriptorHeap();
		
		D3D12_CPU_DESCRIPTOR_HANDLE GetCPUDescriptorHandleForHeapStart();

		DescriptorAllocation Allocate(int count);

		UINT GetOffsetSize() { return inc_size; };

		com_ptr<ID3D12DescriptorHeap> Get() { return _descriptorHeap; };
		
		void Reset();
	};

}