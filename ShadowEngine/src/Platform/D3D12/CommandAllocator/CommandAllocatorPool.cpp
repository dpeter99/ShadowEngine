#include "shpch.h"
#include "CommandAllocatorPool.h"

#include "../DX12RendererAPI.h"

namespace ShadowEngine::Rendering::D3D12 {
	
	CommandAllocator& CommandAllocatorPool::GetFreeCommandAllocator(D3D12_COMMAND_LIST_TYPE type, int frame)
	{
		auto& freeAllocators = free[type];
		
		if(!freeAllocators.empty())
		{
			auto allocator = freeAllocators.front();
			freeAllocators.pop_front();

			allocator.MarkUsed(frame);
			in_flight.emplace(allocator);
			
			return allocator;
		}
		else
		{
			auto alloc = CreateNewCommandAllocator(type);
			alloc->MarkUsed(frame);
			
			this->allocators.emplace(alloc);
			this->in_flight.emplace(alloc);
		}
	}



	void CommandAllocatorPool::CheckFinished(int frame)
	{
		for each (auto& list in this->in_flight)
		{
			for each (auto& allocator in list.second)
			{
				if(allocator.CheckFinished(frame))
				{
					list.second.remove(allocator);
					free[list.first].push_back(allocator);
				}
			}
		}
	}


	Ref<CommandAllocator> CommandAllocatorPool::CreateNewCommandAllocator(D3D12_COMMAND_LIST_TYPE type) const
	{
		com_ptr<ID3D12CommandAllocator> commandAllocator;
		
		DX_API("Failed to create command allocator")
			DX12RendererAPI::device->CreateCommandAllocator(type, IID_PPV_ARGS(commandAllocator.GetAddressOf()));

		return std::make_shared<CommandAllocator>(commandAllocator);
	}
}
