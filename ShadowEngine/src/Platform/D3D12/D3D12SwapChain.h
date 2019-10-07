#pragma once
#include "Platform/D3D12/Common.h"
#include "D3D12CommandQueue.h"
#include "D3D12DescriptorHeap.h"

namespace ShadowEngine::Rendering::D3D12 {

	class D3D12SwapChain
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
		float aspectRatio;

		unsigned int frameIndex;
	public:
		void CreateSwapchain(ShadowEngine::Ref<D3D12::D3D12CommandQueue> commandQueue);
		void CreateSwapchainResources();
		
		D3D12SwapChain(ShadowEngine::Ref<D3D12::D3D12CommandQueue> commandQueue);

		D3D12_RECT GetScissorRect() { return scissorRect; };
	};

}
