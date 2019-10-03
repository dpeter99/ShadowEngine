#pragma once

#include "Common.h"

namespace ShadowEngine::Rendering::D3D12 {

	class D3D12CommandQueue
	{
		com_ptr<ID3D12CommandQueue> commandQueue{ nullptr };

	public:
		D3D12CommandQueue();

	};
}
