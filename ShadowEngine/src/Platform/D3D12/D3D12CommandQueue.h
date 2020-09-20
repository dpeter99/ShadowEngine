#pragma once

#include "Common.h"
#include "CommandList.h"
#include "D3D12Fence.h"

namespace ShadowEngine::Rendering::D3D12 {
	//class D3D12Fence;

	class D3D12CommandQueue
	{
		/// <summary>
		/// The actual Dx12 command queue
		/// </summary>
		com_ptr<ID3D12CommandQueue> commandQueue{ nullptr };

		/// <summary>
		/// The fence for this command queue
		/// </summary>
		D3D12Fence fence;

		/// <summary>
		/// The value that was last used on this command queue
		/// </summary>
		uint64_t fence_value = 0;

	public:
		D3D12CommandQueue(D3D12_COMMAND_LIST_TYPE type = D3D12_COMMAND_LIST_TYPE_DIRECT);

		void SetName(std::wstring name);

		
		/**
		 * \brief Return the internal Dx12 pointer
		 * \return com_ptr of the command queue
		 */
		com_ptr<ID3D12CommandQueue> GetInternalPtr() const { return commandQueue; }

		
		/**
		 * \brief Executes a list of commands
		 * \param commandList the list of commands ot execute
		 */
		void Execute(Ref<CommandList> commandList);

		uint64_t Signal();

		uint64_t GetNextSignalValue();

		void WaitForFenceValue(uint64_t value);

		uint64_t GetCompletedValue();
	};
}
