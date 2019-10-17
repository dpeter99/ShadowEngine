#pragma once

#include "Common.h"

namespace ShadowEngine::Rendering::D3D12 {

	class D3D12Fence
	{
		com_ptr<ID3D12Fence> fence;
	public:
		D3D12Fence();
		
		UINT64 GetCompletedValue();
		
		void SetEventOnCompletion(const UINT64 fv, HANDLE fenceEvent);

		com_ptr<ID3D12Fence> GetFencePointer() { return fence; };
	};

}
