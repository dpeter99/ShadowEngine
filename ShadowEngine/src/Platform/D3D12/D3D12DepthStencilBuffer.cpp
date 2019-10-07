#include "shpch.h"
#include "D3D12DepthStencilBuffer.h"
#include "D3D12RendererAPI.h"

ShadowEngine::Rendering::D3D12::D3D12DepthStencilBuffer::D3D12DepthStencilBuffer(Ref<D3D12::D3D12DescriptorHeap> heap,Ref<D3D12::D3D12SwapChain> swap_chain)
{
	D3D12_CLEAR_VALUE depthOptimizedClearValue = {};
	depthOptimizedClearValue.Format = DXGI_FORMAT_D32_FLOAT;
	depthOptimizedClearValue.DepthStencil.Depth = 1.0f;
	depthOptimizedClearValue.DepthStencil.Stencil = 0;

	auto resource_desc = CD3DX12_RESOURCE_DESC::Tex2D(DXGI_FORMAT_D32_FLOAT, swap_chain->GetScissorRect().right,
		swap_chain->GetScissorRect().bottom, 1, 0, 1, 0,
		D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL);
	DX_API("Failed to create Depth Stencil buffer")
	D3D12RendererAPI::device->CreateCommittedResource(
			&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT),
			D3D12_HEAP_FLAG_NONE,
			&resource_desc,
			D3D12_RESOURCE_STATE_DEPTH_WRITE,
			&depthOptimizedClearValue,
			IID_PPV_ARGS(depthStencilBuffer.GetAddressOf()));

	D3D12_DEPTH_STENCIL_VIEW_DESC depthStencilDesc = {};
	depthStencilDesc.Format = DXGI_FORMAT_D32_FLOAT;
	depthStencilDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
	depthStencilDesc.Flags = D3D12_DSV_FLAG_NONE;

	D3D12RendererAPI::device->CreateDepthStencilView(
		depthStencilBuffer.Get(),
		&depthStencilDesc,
		heap->GetCPUDescriptorHandleForHeapStart());
}
