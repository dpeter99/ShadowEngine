#include "shpch.h"
#include "D3D12ConstantBuffer.h"
#include "D3D12RendererAPI.h"

namespace ShadowEngine::Rendering::D3D12 {
	D3D12ConstantBuffer::D3D12ConstantBuffer(size_t size, std::wstring debug_name):
		mappedPtr{nullptr},
		constantBuffer{nullptr},
		debug_name( debug_name)
	{
		actual_size = (size + 255) & ~255;
		CreateResources(actual_size);
	}

	D3D12ConstantBuffer::~D3D12ConstantBuffer()
	{
		ReleaseResources();
	}

	void D3D12ConstantBuffer::CreateResources(size_t size)
	{
		DX_API("Failed to create constant buffer resource")
			D3D12RendererAPI::device->CreateCommittedResource(
				&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
				D3D12_HEAP_FLAG_NONE,
				&CD3DX12_RESOURCE_DESC::Buffer(size),
				D3D12_RESOURCE_STATE_GENERIC_READ,
				nullptr,
				IID_PPV_ARGS(constantBuffer.GetAddressOf()));

		CD3DX12_RANGE rr(0, 0);
		DX_API("Failed to map constant buffer")
			constantBuffer->Map(0, &rr, reinterpret_cast<void**>(&mappedPtr));

		// for debugging purposes, this will name and index the constant buffers for easier identifications
		static int Id = 0;
		std::wstringstream wss;
		wss << "CB(" << debug_name << ")#" << Id++;
		constantBuffer->SetName(wss.str().c_str());
	}

	D3D12_GPU_VIRTUAL_ADDRESS D3D12ConstantBuffer::GetGPUVirtualAddress() const
	{
		return constantBuffer->GetGPUVirtualAddress();
	}

	void D3D12ConstantBuffer::ReleaseResources()
	{
		if (constantBuffer != nullptr)
		{
			constantBuffer->Unmap(0, nullptr);
			constantBuffer.Reset();
		}
		mappedPtr = nullptr;
	}

	void D3D12ConstantBuffer::Upload(void* data, size_t size)
	{
		memcpy(mappedPtr, data, size);
	}
}
