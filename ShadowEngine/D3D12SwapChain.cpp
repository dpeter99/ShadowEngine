#include "shpch.h"
#include "D3D12SwapChain.h"
#include "Platform/D3D12/D3D12RendererAPI.h"
#include "Platform/D3D12/D3D12CommandQueue.h"

namespace ShadowEngine::Rendering::D3D12 {

	D3D12SwapChain::D3D12SwapChain(ShadowEngine::Ref<D3D12::D3D12CommandQueue> commandQueue)
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
			(HWND)D3D12::D3D12RendererAPI::ctx->m_WindowHandle,
			&swapChainDesc,
			&swapChainFullscreenDesc,
			NULL,
			tempSwapChain.GetAddressOf()
		);

		DX_API("Failed to cast swap chain")
			tempSwapChain.As(&swapChain);
	}

}