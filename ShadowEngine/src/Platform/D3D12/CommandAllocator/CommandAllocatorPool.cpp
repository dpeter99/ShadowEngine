#include "shpch.h"
#include "CommandAllocatorPool.h"

#include "../DX12RendererAPI.h"

namespace ShadowEngine::Rendering::D3D12 {
	
	Ref<CommandAllocator> CommandAllocatorPool::GetFreeCommandAllocator(D3D12_COMMAND_LIST_TYPE type, int frame, Ref<D3D12CommandQueue> queue)
	{
		auto& freeAllocators = free_list[type];

		Ref<CommandAllocator> alloc;
		
		if(!freeAllocators.empty())
		{
			alloc = freeAllocators.back();
			freeAllocators.pop_back();
		}
		else
		{
			alloc = CreateNewCommandAllocator(type);
			this->allocators[type].push_back(alloc);
		}

		if (frame != -1) {
			alloc->MarkUsed(frame, queue);
		}

		this->in_flight[type].push_back(alloc);
		
		return alloc;
	}

	void CommandAllocatorPool::CheckFinished(int frame, Ref<D3D12CommandQueue> queue)
	{
		for (auto& item : in_flight)
		{
			AllocatorList& flight_allocators = item.second;
			
			for (auto allocator : flight_allocators)
			{
				if (allocator.get() == nullptr)
					continue;
				if(allocator->CheckFinished(frame, queue))
				{
					//allocator_list->remove(allocator);
					flight_allocators.erase(std::find(flight_allocators.begin(), flight_allocators.end(), allocator));
					free_list[item.first].push_back(allocator);
					allocator->SetFree();
				}
			}
		}
	}

	std::wstring MakeName(D3D12_COMMAND_LIST_TYPE type)
	{
		static int id[7] = {};
		id[type]++;

		std::wstring name;
		switch (type)
		{
		case D3D12_COMMAND_LIST_TYPE_DIRECT:
			name = L"DIRECT";
			break;
		case D3D12_COMMAND_LIST_TYPE_BUNDLE:
			name = L"BUNDLE";
			break;
		case D3D12_COMMAND_LIST_TYPE_COMPUTE:
			name = L"COMPUTE";
			break;
		case D3D12_COMMAND_LIST_TYPE_COPY:
			name = L"COPY";
			break;
		case D3D12_COMMAND_LIST_TYPE_VIDEO_DECODE:
			name = L"VIDEO_DECODE";
			break;
		case D3D12_COMMAND_LIST_TYPE_VIDEO_PROCESS:
			name = L"VIDEO_PROCESS";
			break;
		case D3D12_COMMAND_LIST_TYPE_VIDEO_ENCODE:
			name = L"VIDEO_ENCODE";
			break;
		default:
			break;
		}


		name += std::to_wstring(id[type]);

		return name;
	}

	Ref<CommandAllocator> CommandAllocatorPool::CreateNewCommandAllocator(D3D12_COMMAND_LIST_TYPE type) const
	{
		
		
		com_ptr<ID3D12CommandAllocator> commandAllocator;
		
		DX_API("Failed to create command allocator")
			DX12RendererAPI::device->CreateCommandAllocator(type, IID_PPV_ARGS(commandAllocator.GetAddressOf()));

		auto allocator = std::make_shared<CommandAllocator>(commandAllocator, type);
		
		allocator->SetName(MakeName(type));
		
		return allocator;
	}

	
}
