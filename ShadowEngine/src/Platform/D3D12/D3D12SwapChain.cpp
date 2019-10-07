#include "shpch.h"
#include "D3D12SwapChain.h"
#include "Platform/D3D12/D3D12RendererAPI.h"
#include "Platform/D3D12/D3D12CommandQueue.h"

namespace ShadowEngine::Rendering::D3D12 {
	
	void D3D12SwapChain::CreateSwapchain(ShadowEngine::Ref<D3D12::D3D12CommandQueue> commandQueue)
	{
		// swap chain creation
		DXGI_SWAP_CHAIN_DESC1 swapChainDesc = { 0 };
		// if you specify width/height as 0, the CreateSwapChainForHwnd will query it from the output window
		swapChainDesc.Width = 0;
		swapChainDesc.Height = 0;
		swapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		swapChainDesc.Stereo = false;
		swapChainDesc.SampleDesc.Count = 1;
		swapChainDesc.SampleDesc.Quality = 0;
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc.BufferCount = 2; // back buffer depth
		swapChainDesc.Scaling = DXGI_SCALING_NONE;
		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;
		swapChainDesc.AlphaMode = DXGI_ALPHA_MODE_IGNORE;
		swapChainDesc.Flags = 0;

		DXGI_SWAP_CHAIN_FULLSCREEN_DESC swapChainFullscreenDesc = { 0 };
		swapChainFullscreenDesc.RefreshRate = DXGI_RATIONAL{ 60, 1 };
		swapChainFullscreenDesc.Windowed = true;
		swapChainFullscreenDesc.Scaling = DXGI_MODE_SCALING_CENTERED;
		swapChainFullscreenDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UPPER_FIELD_FIRST;

		com_ptr<IDXGISwapChain1> tempSwapChain;

		DX_API("Failed to create swap chain for HWND")
			D3D12::D3D12RendererAPI::ctx->dxgiFactory->CreateSwapChainForHwnd(
				commandQueue->GetInternalPtr().Get(),
				(HWND)D3D12::D3D12RendererAPI::ctx->hwnd,
				&swapChainDesc,
				&swapChainFullscreenDesc,
				NULL,
				tempSwapChain.GetAddressOf()
			);

		DX_API("Failed to cast swap chain")
			tempSwapChain.As(&swapChain);
	}

	void D3D12SwapChain::CreateSwapchainResources()
	{
		DXGI_SWAP_CHAIN_DESC scDesc;
		swapChain->GetDesc(&scDesc);

		backBufferDepth = scDesc.BufferCount;

		viewPort.TopLeftX = 0;
		viewPort.TopLeftY = 0;
		viewPort.Width = (float)scDesc.BufferDesc.Width;
		viewPort.Height = (float)scDesc.BufferDesc.Height;
		viewPort.MinDepth = 0.0f;
		viewPort.MaxDepth = 1.0f;

		aspectRatio = viewPort.Width / (float)viewPort.Height;

		scissorRect.left = 0;
		scissorRect.top = 0;
		scissorRect.right = scDesc.BufferDesc.Width;
		scissorRect.bottom = scDesc.BufferDesc.Height;

		// Create Render Target View Descriptor Heap, like a RenderTargetView** on the GPU. A set of pointers.
		rtvDescriptorHeap = std::make_unique<D3D12::D3D12DescriptorHeap>(D3D12_DESCRIPTOR_HEAP_FLAG_NONE, D3D12_DESCRIPTOR_HEAP_TYPE_RTV, backBufferDepth);
		

		rtvHandle = rtvDescriptorHeap->GetCPUDescriptorHandleForHeapStart();
		rtvDescriptorHandleIncrementSize = D3D12RendererAPI::device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

		// Create Render Target Views

		renderTargets.resize(backBufferDepth);

		for (unsigned int i = 0; i < backBufferDepth; ++i) {
			DX_API("Failed to get swap chain buffer")
				swapChain->GetBuffer(i, IID_PPV_ARGS(renderTargets[i].GetAddressOf()));

			CD3DX12_CPU_DESCRIPTOR_HANDLE cpuHandle{ rtvHandle };
			cpuHandle.Offset(i * rtvDescriptorHandleIncrementSize);

			D3D12RendererAPI::device->CreateRenderTargetView(renderTargets[i].Get(), nullptr, cpuHandle);
		}

		frameIndex = swapChain->GetCurrentBackBufferIndex();
	}

	D3D12SwapChain::D3D12SwapChain(ShadowEngine::Ref<D3D12::D3D12CommandQueue> commandQueue)
	{
		CreateSwapchain(commandQueue);

		CreateSwapchainResources();
	}

}