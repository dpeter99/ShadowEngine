#include "shpch.h"
#include "CommandAllocator.h"

namespace ShadowEngine::Rendering::D3D12 {

	CommandAllocator::CommandAllocator(com_ptr<ID3D12CommandAllocator> commandAllocator, D3D12_COMMAND_LIST_TYPE type) :
	m_commandAllocator(commandAllocator), type(type)
	
	{

	}

	void CommandAllocator::MarkUsed(int frame)
	{
		this->free = false;
		this->freeFrame = frame;
	}

	D3D12_COMMAND_LIST_TYPE CommandAllocator::GetType()
	{
		return this->type;
	}

	bool CommandAllocator::CheckFinished(int frame)
	{
		return frame >= freeFrame;
	}

}