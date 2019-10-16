#include "shpch.h"
#include "D3D12CommandList.h"
#include "D3D12RendererAPI.h"

namespace ShadowEngine::Rendering::D3D12 {
	D3D12CommandList::D3D12CommandList()
	{
		DX_API("Failed to create command allocator")
		D3D12RendererAPI::device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(commandAllocator.GetAddressOf()));

		DX_API("Failed to greate graphics command list")
		D3D12RendererAPI::device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, commandAllocator.Get(), nullptr, IID_PPV_ARGS(commandList.GetAddressOf()));
	}

	void D3D12CommandList::Reset()
	{
		commandAllocator->Reset();
		commandList->Reset(commandAllocator.Get(), nullptr);
	}

	void D3D12CommandList::SetViewports(D3D12_VIEWPORT viewPort)
	{
		commandList->RSSetViewports(1, &viewPort);
	}

	void D3D12CommandList::SetScissorRects(D3D12_RECT scissorRect)
	{
		commandList->RSSetScissorRects(1, &scissorRect);
	}

	void D3D12CommandList::ResourceBarrier(D3D12_RESOURCE_BARRIER* barrier)
	{
		commandList->ResourceBarrier(1, barrier);
	}

	void D3D12CommandList::SetRenderTargets(Ref<D3D12SwapChain> swapchain, Ref<D3D12DepthBuffer> depthBuffer)
	{
		renderTarget = swapchain->GetCurrentRenderTargetDescriptor();
		this->depthBuffer = depthBuffer->GetDescriptorHandle();
		commandList->OMSetRenderTargets(1, &renderTarget, FALSE, &this->depthBuffer);
	}

	void D3D12CommandList::ClearRenderTargetView(const float* color)
	{
		commandList->ClearRenderTargetView(renderTarget, color, 0, nullptr);
	}

	void D3D12CommandList::ClearDepthStencilView(float depth, uint8_t stencil)
	{
		commandList->ClearDepthStencilView(depthBuffer, D3D12_CLEAR_FLAG_DEPTH, depth, stencil, 0, nullptr);
	}

	void D3D12CommandList::Close()
	{
		DX_API("Failed to close command list")
			commandList->Close();
	}
}
