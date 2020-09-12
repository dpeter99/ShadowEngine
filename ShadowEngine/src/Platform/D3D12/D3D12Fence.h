#pragma once

#include "Common.h"

namespace ShadowEngine::Rendering::D3D12 {

	/// <summary>
	/// Represents the dx12 fence
	/// </summary>
	/// 
	/// A fence is used for synchronizing between the GPU and the CPU with an int
	/// THis int can be changed form cpu side and waited for on the gpu or the other way round.
	class D3D12Fence
	{
		/// <summary>
		/// The underlying ID3D12Fence instance
		/// </summary>
		com_ptr<ID3D12Fence> fence;

		/// <summary>
		/// The windows event used to wait for a change
		/// </summary>
		HANDLE fenceEvent;

		/// <summary>
		/// The current value of the fence
		/// </summary>
		//uint64_t fenceValue;

	public:
		D3D12Fence();
		
		UINT64 GetCompletedValue();
		
		void SetEventOnCompletion(const UINT64 fv, HANDLE fenceEvent);

		com_ptr<ID3D12Fence> GetFencePointer() { return fence; };

		void WaitForValue(uint64_t value, std::chrono::milliseconds duration = std::chrono::milliseconds::max());
	};

}
