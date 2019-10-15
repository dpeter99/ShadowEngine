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
	class D3D12SwapChain : public SwapChain
	{
		com_ptr<IDXGISwapChain3> swapChain{ nullptr };

		// swap chain resources
		D3D12_VIEWPORT viewPort;
		D3D12_RECT scissorRect;
		unsigned int backBufferDepth;
		unsigned int rtvDescriptorHandleIncrementSize;
		D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle;
		Ref<D3D12DescriptorHeap> rtvDescriptorHeap;
		std::vector<com_ptr<ID3D12Resource>> renderTargets;
		
	public:
		D3D12SwapChain(Ref<D3D12CommandQueue> commandQueue);
		
		void CreateSwapchain(Ref<D3D12CommandQueue> commandQueue);
		void CreateSwapchainResources();
		
		

		D3D12_RECT GetScissorRect() { return scissorRect; }
		void SetAspectRatio() override;
		void SetFrameIndex() override;;
	};

}
