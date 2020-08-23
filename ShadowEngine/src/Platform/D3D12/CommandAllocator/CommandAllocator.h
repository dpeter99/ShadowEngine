#pragma once

#include "../Common.h"

namespace ShadowEngine::Rendering::D3D12 {

	/// <summary>
	/// Command allocators represent the render commands on the GPU side
	/// </summary>
	///
	/// Command allocators are the GPU memory that is used for storing the render commands
	/// A Command list is used to record new commands into them. A command allocators memory cna be reused when all of the recorded commands finished executing.
	class CommandAllocator
	{
		com_ptr<ID3D12CommandAllocator> m_commandAllocator;
		bool free = true;
		int freeFrame = -1;
		D3D12_COMMAND_LIST_TYPE type;


	public:

		/// <summary>
		/// Standard constructor
		/// </summary>
		/// <param name="commandAllocator">The allocator that we are going to encompass</param>
		/// <param name="type">The tpe of allocator that we are holding</param>
		CommandAllocator(com_ptr<ID3D12CommandAllocator> commandAllocator, D3D12_COMMAND_LIST_TYPE type);

		/// <summary>
		/// Returns the underlying allocator
		/// </summary>
		/// <returns>The com pointer to the allocator</returns>
		com_ptr<ID3D12CommandAllocator> const Allocator() const { return m_commandAllocator; }

		/// <summary>
		/// Marks the allocator as in use and sets the frame that it is used in
		/// </summary>
		/// <param name="frame">The frame that this allocator can be reused after</param>
		void MarkUsed(int frame);

		/// <summary>
		/// Returns the type of the allocator.
		/// </summary>
		/// <returns></returns>
		D3D12_COMMAND_LIST_TYPE GetType();

		/// <summary>
		/// Checks if the given frame frees this allocator for further use
		/// </summary>
		/// <param name="frame">The frame that was last rendered</param>
		/// <returns>Weather this allocator can be reused or not</returns>
		///
		/// If the frame parameter is bigger than the frame this allocator was used in it returns true.
		bool CheckFinished(int frame);

		

	};

}