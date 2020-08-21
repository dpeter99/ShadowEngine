#pragma once

#include "../Common.h"

namespace ShadowEngine::Rendering::D3D12 {


	class CommandAllocator
	{
		com_ptr<ID3D12CommandAllocator> m_commandAllocator;
		bool free = true;
		int freeFrame = -1;
		D3D12_COMMAND_LIST_TYPE type;


	public:

		CommandAllocator(com_ptr<ID3D12CommandAllocator> commandAllocator);

		void MarkUsed(int frame);
		D3D12_COMMAND_LIST_TYPE GetType();
		bool CheckFinished(int frame);

	};

}