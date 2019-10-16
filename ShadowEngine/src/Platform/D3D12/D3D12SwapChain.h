#pragma once
#include "Platform/D3D12/Common.h"
#include "D3D12CommandQueue.h"
#include "D3D12DescriptorHeap.h"
#include "ShadowRenderer/SwapChain.h"

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

		// swap chain resources

		//Rects
		
		D3D12_VIEWPORT viewPort;
		D3D12_RECT scissorRect;

		float aspectRatio;
		
		/**
		 * \brief The number of render targets
		 */
		unsigned int backBufferDepth = 2;
		
		

		
		/**
		 * \brief DescriptorHeap for Render targets views
		 */
		Ref<D3D12DescriptorHeap> rtvDescriptorHeap;
		
		/**
		 * \brief Size of the Render Target Views
		 */
		unsigned int rtvDescriptorHandleIncrementSize;
		
		/**
		 * \brief The start of the descriptor array
		 */
		D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle;

		
		/**
		 * \brief List of render targets
		 */
		std::vector<com_ptr<ID3D12Resource>> renderTargets;

		/**
		 * \brief The active render targets index
		 */
		unsigned int frameIndex;

	public:
		D3D12SwapChain(Ref<D3D12CommandQueue> commandQueue);
		~D3D12SwapChain();

		
		/**
		 * \brief Creates the base swap chain
		 * \param commandQueue the command queue to use
		 */
		void CreateSwapchain(Ref<D3D12CommandQueue> commandQueue);
		void CreateSwapchainResources();


		void SetViewPort(D3D12_VIEWPORT rect)
		{
			viewPort = rect;
		}
		D3D12_VIEWPORT GetViewPort() { return viewPort; }

		
		void SetScissorRect(D3D12_RECT rect)
		{
			scissorRect = rect;
		}
		D3D12_RECT GetScissorRect() { return scissorRect; }

		com_ptr<ID3D12Resource> GetRenderTarget(int i)
		{
			return renderTargets[i];
		}

		com_ptr<ID3D12Resource> GetCurrentRenderTarget()
		{
			return renderTargets[frameIndex];
		}

		void ReleaseSwapChainResources();

		virtual void Resize(int width, int height);
		
		
	};

}
