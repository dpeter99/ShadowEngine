#pragma once
#include "ShadowRenderer/CommandList.h"
#include "Common.h"

namespace ShadowEngine::Rendering::D3D12 {

	class D3D12CommandList : public CommandList
	{
		com_ptr<ID3D12CommandAllocator> commandAllocator;
		com_ptr<ID3D12GraphicsCommandList> commandList;
	public:
		D3D12CommandList();
		
		void Reset() override;
	};

}
