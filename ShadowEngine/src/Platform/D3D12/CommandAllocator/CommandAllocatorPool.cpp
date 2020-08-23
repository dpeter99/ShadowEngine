#include "shpch.h"
#include "CommandAllocatorPool.h"

#include "../DX12RendererAPI.h"

namespace ShadowEngine::Rendering::D3D12 {
	
	Ref<CommandAllocator> CommandAllocatorPool::GetFreeCommandAllocator(D3D12_COMMAND_LIST_TYPE type, int frame)
	{
		auto& freeAllocators = free_list[type];
		
		if(!freeAllocators.empty())
		{
			auto allocator = freeAllocators.back();
			freeAllocators.pop_back();

			allocator->MarkUsed(frame);
			in_flight[type].push_back(allocator);
			
			return allocator;
		}
		else
		{
			auto alloc = CreateNewCommandAllocator(type);
			alloc->MarkUsed(frame);
			
			this->allocators[type].push_back(alloc);
			this->in_flight[type].push_back(alloc);

			return alloc;
		}
	}



	void CommandAllocatorPool::CheckFinished(int frame)
	{
		for (auto& item : in_flight)
		{
			AllocatorList& allocator_list = item.second;
			
				for (auto& allocator : allocator_list)
				{
					if(allocator->CheckFinished(frame))
					{
						//allocator_list->remove(allocator);
						allocator_list.erase(std::find(allocator_list.begin(), allocator_list.end(), allocator));
						free_list[item.first].push_back(allocator);
					}
				}
			/*
			AllocatorList::iterator i = allocator_list.begin();
			while (i != allocator_list.end())
			{
				auto& allocator = *i;
				if (allocator->CheckFinished(frame))
				{
					AllocatorList::iterator prev = i++;
					allocator_list.erase(prev);
					free[item.first].push_back(allocator);
				}
				
			}
			*/
		}
	}


	Ref<CommandAllocator> CommandAllocatorPool::CreateNewCommandAllocator(D3D12_COMMAND_LIST_TYPE type) const
	{
		com_ptr<ID3D12CommandAllocator> commandAllocator;
		
		DX_API("Failed to create command allocator")
			DX12RendererAPI::device->CreateCommandAllocator(type, IID_PPV_ARGS(commandAllocator.GetAddressOf()));

		return std::make_shared<CommandAllocator>(commandAllocator, type);
	}
}
