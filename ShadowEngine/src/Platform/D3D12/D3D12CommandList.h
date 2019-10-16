#pragma once
#include "ShadowRenderer/CommandList.h"
#include "Common.h"
#include "D3D12DepthBuffer.h"

namespace ShadowEngine::Rendering::D3D12 {
	class D3D12SwapChain;

	class D3D12CommandList
	{
		com_ptr<ID3D12CommandAllocator> commandAllocator;
		com_ptr<ID3D12GraphicsCommandList> commandList;

		D3D12_CPU_DESCRIPTOR_HANDLE renderTarget;
		D3D12_CPU_DESCRIPTOR_HANDLE depthBuffer;
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

		/**
		 * \brief Set the render targets used in this command list
		 * \param swapchain The swap chain to get the render target form
		 * \param depthBuffer The depth buffer to use
		 */
		void SetRenderTargets(
			Ref<D3D12SwapChain> swapchain,
			Ref<D3D12DepthBuffer> depthBuffer);

		void ClearRenderTargetView(const float* color);

		void ClearDepthStencilView(float depth, uint8_t stencil);
		void Close();
	};

}
