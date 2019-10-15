#pragma once

#include "Common.h"
#include "ShadowRenderer/CommandQueue.h"

namespace ShadowEngine::Rendering::D3D12 {

	class D3D12CommandQueue : public CommandQueue
	{
		com_ptr<ID3D12CommandQueue> commandQueue{ nullptr };

	public:
		D3D12CommandQueue();

		com_ptr<ID3D12CommandQueue> GetInternalPtr() { return commandQueue; }
	};
}
