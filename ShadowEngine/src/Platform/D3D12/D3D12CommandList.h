#pragma once
#include "ShadowRenderer/CommandList.h"
#include "Common.h"

namespace ShadowEngine::Rendering::D3D12 {
	class D3D12SwapChain;

	class D3D12CommandList
	{
		com_ptr<ID3D12CommandAllocator> commandAllocator;
		com_ptr<ID3D12GraphicsCommandList> commandList;
	public:
		D3D12CommandList();

		/**
		 * \brief Resets the Command List
		 * Should only be used when we are sure it is not in use
		 */
		void Reset();


		void SetViewports(D3D12_VIEWPORT viewPort);

		void SetScissorRects(D3D12_RECT scissorRect);

		/**
		 * \brief Adds a new resource barrier to the command list
		 * \param barrier The barrier to use
		 * Used to wait for a resource transition to happen (eg. rendertarget is available)
		 */
		void ResourceBarrier(D3D12_RESOURCE_BARRIER* barrier);

		void SetRenderTargets(Ref<D3D12SwapChain> swapchain);
	};

}
