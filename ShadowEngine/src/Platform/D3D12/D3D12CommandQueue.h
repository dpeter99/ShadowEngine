#pragma once

#include "Common.h"
#include "ShadowRenderer/CommandQueue.h"

namespace ShadowEngine::Rendering::D3D12 {

	class D3D12CommandQueue
	{
		
		/**
		 * \brief The actual Dx12 command queue
		 */
		com_ptr<ID3D12CommandQueue> commandQueue{ nullptr };

	public:
		D3D12CommandQueue();

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
	};
}
