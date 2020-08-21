#pragma once

#include "../Common.h"
#include "CommandAllocator.h"

namespace ShadowEngine::Rendering::D3D12 {

	
	class CommandAllocatorPool
	{
		using AllocatorList = std::list<Ref<CommandAllocator>>;
		using AllocatorRefList = std::list<CommandAllocator&>;
		
		std::map<int, AllocatorList> allocators;
		std::map<int, AllocatorRefList> free;
		std::map<int, AllocatorRefList> in_flight;

	public:

		/// <summary>
		/// Returns a new command allocators to be used
		/// </summary>
		///
		/// 
		/// <param name="type">The type of allocator that is needed</param>
		/// <param name="frame">The frame this allocator is used in</param>
		/// <returns>A command allocator to use</returns>
		/// 
		/// This finds a free command allocator or creates a new one. The Command allocator will be freed when the specified frame is finished
		CommandAllocator& GetFreeCommandAllocator(D3D12_COMMAND_LIST_TYPE type, int frame);
		
		void CheckFinished(int frame);

	private:

		/// <summary>
		/// Creates a new command allocator.
		/// </summary>
		/// <param name="type">The type of the new command allocator</param>
		/// <returns></returns>
		Ref<CommandAllocator> CreateNewCommandAllocator(D3D12_COMMAND_LIST_TYPE type) const;
	};

}
