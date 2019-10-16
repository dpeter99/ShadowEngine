#include "shpch.h"
#include "D3D12SwapChain.h"
#include "Platform/D3D12/D3D12RendererAPI.h"
#include "Platform/D3D12/D3D12CommandQueue.h"

namespace ShadowEngine::Rendering::D3D12 {

	D3D12SwapChain::D3D12SwapChain(Ref<D3D12CommandQueue> commandQueue, int width, int height)
	{
		// swap chain creation
		DXGI_SWAP_CHAIN_DESC1 swapChainDesc = { 0 };
		// if you specify width/height as 0, the CreateSwapChainForHwnd will query it from the output window
		swapChainDesc.Width = width;
		swapChainDesc.Height = height;
		swapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		swapChainDesc.Stereo = false;
		swapChainDesc.SampleDesc.Count = 1;
		swapChainDesc.SampleDesc.Quality = 0;
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc.BufferCount = backBufferDepth;
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

		CreateSwapchainResources();
	}

	D3D12SwapChain::~D3D12SwapChain()
	{
	}

	void D3D12SwapChain::CreateSwapchainResources()
	{
		DXGI_SWAP_CHAIN_DESC scDesc;
		swapChain->GetDesc(&scDesc);		

		// Create Render Target View Descriptor Heap, like a RenderTargetView** on the GPU. A set of pointers.
		rtvDescriptorHeap = std::make_unique<D3D12DescriptorHeap>(D3D12_DESCRIPTOR_HEAP_FLAG_NONE, D3D12_DESCRIPTOR_HEAP_TYPE_RTV, backBufferDepth);
		
		rtvHandle = rtvDescriptorHeap->GetCPUDescriptorHandleForHeapStart();
		rtvDescriptorHandleIncrementSize = D3D12RendererAPI::device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

		// Create Render Target Views

		//Pre size the vector
		renderTargets.resize(backBufferDepth);

		for (unsigned int i = 0; i < backBufferDepth; ++i) {
			//Get the texture
			DX_API("Failed to get swap chain buffer")
				swapChain->GetBuffer(i, IID_PPV_ARGS(renderTargets[i].GetAddressOf()));

			//offset the pointer
			CD3DX12_CPU_DESCRIPTOR_HANDLE cpuHandle{ rtvHandle };
			cpuHandle.Offset(i * rtvDescriptorHandleIncrementSize);

			//Create the view
			D3D12RendererAPI::device->CreateRenderTargetView(renderTargets[i].Get(), nullptr, cpuHandle);
		}

		//Assign the current render target texture index
		frameIndex = swapChain->GetCurrentBackBufferIndex();
	}

	CD3DX12_CPU_DESCRIPTOR_HANDLE D3D12SwapChain::GetCurrentRenderTargetDescriptor() const
	{
		CD3DX12_CPU_DESCRIPTOR_HANDLE r_handle(rtvDescriptorHeap->GetCPUDescriptorHandleForHeapStart(), frameIndex, rtvDescriptorHandleIncrementSize);
		
		return r_handle;
	}

	void D3D12SwapChain::ReleaseSwapChainResources()
	{
		for (com_ptr<ID3D12Resource>& i : renderTargets)
		{
			i.Reset();
		}
		renderTargets.clear();
		rtvDescriptorHeap->Reset();
	}

	void D3D12SwapChain::Resize(int width, int height)
	{
		ReleaseSwapChainResources();
		DX_API("Failed to resize swap chain")
			swapChain->ResizeBuffers(backBufferDepth, 0, 0, DXGI_FORMAT_UNKNOWN, 0);
		CreateSwapchainResources();
	}



	

}