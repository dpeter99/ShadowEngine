#pragma once
#include "Platform/D3D12/Common.h"
#include "D3D12CommandQueue.h"
#include "Descriptors/DescriptorAllocation.h"

namespace ShadowEngine::Rendering::D3D12 {

	/**
	 * \brief Dx12 Swap Chain
	 * Used for swapping the render and present render targets
	 */
	class D3D12SwapChain
	{
		/**
		 * \brief The actual Dx12 swap chain pointer
		 */
		com_ptr<IDXGISwapChain3> swapChain{ nullptr };
		
		/**
		 * \brief The number of render targets
		 */
		unsigned int backBufferDepth = 2;
		
		
		/**
		 * \brief DescriptorHeap for Render targets views
		 */
		//Ref<D3D12DescriptorHeap> rtvDescriptorHeap;
		
		/**
		 * \brief Size of the Render Target Views
		 */
		//unsigned int rtvDescriptorHandleIncrementSize;
		
		/**
		 * \brief The start of the descriptor array
		 */
		//D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle;

		DescriptorAllocation rtvDescriptors;
		
		/**
		 * \brief List of render targets
		 */
		std::vector<com_ptr<ID3D12Resource>> renderTargets;

		/**
		 * \brief The active render targets index
		 */
		unsigned int frameIndex;

	public:
		D3D12SwapChain(Ref<D3D12CommandQueue> commandQueue, int width, int height);
		~D3D12SwapChain();

		
		/**
		 * \brief Creates the base swap chain
		 * \param commandQueue the command queue to use
		 */
		void CreateSwapchain(Ref<D3D12CommandQueue> commandQueue);
		void CreateSwapchainResources();

		com_ptr<ID3D12Resource> GetRenderTarget(int i)
		{
			return renderTargets[i];
		}

		com_ptr<ID3D12Resource> GetCurrentRenderTarget()
		{
			return renderTargets[frameIndex];
		}

		/**
		 * \brief Returns a new Descriptor handle to the active render target
		 * \return The Descriptor handle
		 */
		CD3DX12_CPU_DESCRIPTOR_HANDLE GetCurrentRenderTargetDescriptor() const;

		void ReleaseSwapChainResources();

		void Resize(int width, int height);
		
		void Present(UINT SyncInterval, UINT Flags);

		/**
		 * \brief Returns the active Render Target index
		 * \return The index of the current render target
		 */
		int GetCurrentBackBufferIndex();
		
		/**
		 * \brief Updates the Current render target index
		 * Call this after you changed the active render target
		 */
		void UpdateCurrentBackBufferIndex();
	};

}
