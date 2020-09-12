#include "shpch.h"
#include "CommandAllocator.h"

namespace ShadowEngine::Rendering::D3D12 {

	CommandAllocator::CommandAllocator(com_ptr<ID3D12CommandAllocator> commandAllocator, D3D12_COMMAND_LIST_TYPE type) :
	m_commandAllocator(commandAllocator), type(type)
	
	{
		static int nextID = 0;
		id = nextID++;
	}

	void CommandAllocator::MarkUsed(int frame, Ref<D3D12CommandQueue> queue)
	{
		this->free = false;
		this->freeFrame = frame;
		this->freeCommandQueue = queue
	}

	void CommandAllocator::SetFree()
	{
		this->freeFrame = -1;
		this->free = true;
	}

	D3D12_COMMAND_LIST_TYPE CommandAllocator::GetType()
	{
		return this->type;
	}

	bool CommandAllocator::CheckFinished(int frame, Ref<D3D12CommandQueue> queue)
	{

		return frame >= freeFrame && queue == freeCommandQueue;
	}

}