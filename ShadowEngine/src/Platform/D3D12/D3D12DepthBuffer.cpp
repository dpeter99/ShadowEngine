#include "shpch.h"
#include "D3D12DepthBuffer.h"
#include "D3D12RendererAPI.h"

namespace ShadowEngine::Rendering::D3D12 {

	D3D12DepthBuffer::D3D12DepthBuffer(D3D12_RECT scissorRect)
	{
		
		auto depthFormat = DXGI_FORMAT_D32_FLOAT;

		D3D12_DESCRIPTOR_HEAP_DESC dsHeapDesc = {};
		dsHeapDesc.NumDescriptors = 1;
		dsHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
		dsHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;

		DX_API("Failed to create depth stencil descriptor heap")
			D3D12RendererAPI::device->CreateDescriptorHeap(&dsHeapDesc, IID_PPV_ARGS(this->descriptorHeap.GetAddressOf()));


		
		D3D12_CLEAR_VALUE depthOptimizedClearValue = {};
		depthOptimizedClearValue.Format = depthFormat;
		depthOptimizedClearValue.DepthStencil.Depth = 1.0f;
		depthOptimizedClearValue.DepthStencil.Stencil = 0;
		
		DX_API("Failed to create Depth Stencil buffer")
			D3D12RendererAPI::device->CreateCommittedResource(
				&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT),
				D3D12_HEAP_FLAG_NONE,
				&CD3DX12_RESOURCE_DESC::Tex2D(depthFormat, scissorRect.right, scissorRect.bottom, 1, 0, 1, 0, D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL),
				D3D12_RESOURCE_STATE_DEPTH_WRITE,
				&depthOptimizedClearValue,
				IID_PPV_ARGS(depthStencilBuffer.GetAddressOf()));

		depthStencilBuffer->SetName(L"Depth Stencil Buffer");

		D3D12_DEPTH_STENCIL_VIEW_DESC depthStencilDesc = {};
		depthStencilDesc.Format = depthFormat;
		depthStencilDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
		depthStencilDesc.Flags = D3D12_DSV_FLAG_NONE;

		D3D12RendererAPI::device->CreateDepthStencilView(depthStencilBuffer.Get(), &depthStencilDesc, descriptorHeap->GetCPUDescriptorHandleForHeapStart());
	}

	CD3DX12_CPU_DESCRIPTOR_HANDLE D3D12DepthBuffer::GetDescriptorHandle()
	{
		CD3DX12_CPU_DESCRIPTOR_HANDLE r_handle(descriptorHeap->GetCPUDescriptorHandleForHeapStart());

		return r_handle;
	}
}
