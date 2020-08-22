#pragma once
#include "Platform/D3D12/Common.h"
#include "D3D12CommandQueue.h"
#include "Descriptors/DescriptorAllocation.h"

namespace ShadowEngine::Rendering::D3D12 {

	/// <summary>
	/// Dx12 Swap Chain
	/// </summary>
	///
	/// Contains multiple render targets that are used in rotation.
	/// One of them is used for drawing to the screen while the others can be used as a render target.
	class D3D12SwapChain
	{
		/// <summary>
		/// The actual Dx12 swap chain pointer
		/// </summary>
		///
		/// This is the actual underlying DX12 swap chain. Should not be handled on it's own.
		com_ptr<IDXGISwapChain3> swapChain{ nullptr };
	

		/// <summary>
		/// The number of render targets
		/// </summary>
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

		/// <summary>
		/// List of render targets
		/// </summary>
		std::vector<com_ptr<ID3D12Resource>> renderTargets;

		/// <summary>
		/// The active render targets index
		/// </summary>
		///
		/// This is the index of the active render target in the frames 
		unsigned int currentBackBufferIndex;

		uint64_t g_FrameFenceValues[2] = {};

	public:
		D3D12SwapChain(Ref<D3D12CommandQueue> commandQueue, int width, int height);
		~D3D12SwapChain();

		/// <summary>
		/// Creates the base swap chain
		/// </summary>
		/// <param name="commandQueue">The command queue that will be used for this swapchain</param>
		void CreateSwapchain(Ref<D3D12CommandQueue> commandQueue);
		void CreateSwapchainResources();

		com_ptr<ID3D12Resource> GetRenderTarget(int i)
		{
			return renderTargets[i];
		}

		com_ptr<ID3D12Resource> GetCurrentRenderTarget()
		{
			return renderTargets[currentBackBufferIndex];
		}


		void SetCurrentRenderTargetFenceValue(uint64_t fence)
		{
			SetRenderTargetFenceValue(currentBackBufferIndex, fence);
		}
		
		void SetRenderTargetFenceValue(int RT, uint64_t fence)
		{
			g_FrameFenceValues[RT] = fence;
		}
		
		uint64_t GetCurrentRenderTargetFenceValue()
		{
			return g_FrameFenceValues[currentBackBufferIndex];
		}
		
		uint64_t GetRenderTargetFenceValue(int RT)
		{
			return g_FrameFenceValues[RT];
		}
		
		/// <summary>
		/// Returns a new Descriptor handle to the active render target
		/// </summary>
		/// <returns>The Descriptor handle</returns>
		CD3DX12_CPU_DESCRIPTOR_HANDLE GetCurrentRenderTargetDescriptor() const;

		void ReleaseSwapChainResources();

		void Resize(int width, int height);
		
		void Present(UINT SyncInterval, UINT Flags);


		/// <summary>
		/// Returns the active Render Target index
		/// </summary>
		/// <returns>The index of the current render target</returns>
		int GetCurrentBackBufferIndex[[deprecated]]();

		/// <summary>
		/// Updates the Current render target index
		/// </summary>
		///
		/// Call this after you changed the active render target
		void FindNextBackBufferIndex();
	};

}
