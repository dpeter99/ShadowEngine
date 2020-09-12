#pragma once

#include "../Common.h"
#include "CommandAllocator.h"

namespace ShadowEngine::Rendering::D3D12 {

	/// <summary>
	/// Provides pooling for the command allocators.
	/// </summary>
	class CommandAllocatorPool
	{
		using AllocatorList = std::vector<Ref<CommandAllocator>>;
		
		std::map<int, AllocatorList> allocators;
		std::map<int, AllocatorList> free_list;
		std::map<int, AllocatorList> in_flight;

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
		Ref<CommandAllocator> GetFreeCommandAllocator(D3D12_COMMAND_LIST_TYPE type, int frame);


		/// <summary>
		/// Checks if any of the in flight allocators can be freed
		/// </summary>
		/// <param name="frame">The frame that finished</param>
		void CheckFinished(int frame, Ref<D3D12CommandQueue> queue);

		std::map<int, AllocatorList>& GetAllAllocaotrs() { return allocators; }
		
	private:

		/// <summary>
		/// Creates a new command allocator.
		/// </summary>
		/// <param name="type">The type of the new command allocator</param>
		/// <returns></returns>
		Ref<CommandAllocator> CreateNewCommandAllocator(D3D12_COMMAND_LIST_TYPE type) const;
	};

}
