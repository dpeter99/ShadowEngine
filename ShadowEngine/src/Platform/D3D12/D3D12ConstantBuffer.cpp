#include "shpch.h"
#include "D3D12ConstantBuffer.h"
#include "DX12RendererAPI.h"

#include <functional>

namespace ShadowEngine::Rendering::D3D12 {
	
	DX12ConstantBuffer::DX12ConstantBuffer(size_t size, std::wstring debug_name):
		Buffer(debug_name),
		mappedPtr{nullptr}
	{
		actual_size = (size + 255) & ~255;

		auto desc = CD3DX12_RESOURCE_DESC::Buffer(actual_size);
		
		SetupResource(desc, debug_name);
	}

	DX12ConstantBuffer::~DX12ConstantBuffer()
	{
		//ReleaseResources();
	}
	
	/*
	void DX12ConstantBuffer::CreateResources(size_t size)
	{
		DX_API("Failed to create constant buffer resource")
			DX12RendererAPI::device->CreateCommittedResource(
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
	*/

	D3D12_GPU_VIRTUAL_ADDRESS DX12ConstantBuffer::GetGPUVirtualAddress() const
	{
		return m_d3d12Resource->GetGPUVirtualAddress();
		
		//return constantBuffer->GetGPUVirtualAddress();
	}
	
	/*
	void DX12ConstantBuffer::ReleaseResources()
	{
		if (constantBuffer != nullptr)
		{
			constantBuffer->Unmap(0, nullptr);
			constantBuffer.Reset();
		}
		mappedPtr = nullptr;
	}
	*/

	void DX12ConstantBuffer::RecordTransfer(ShadowEngine::Ref<CommandList> cmd)
	{
		cmd->XDEP_UploadToBuffer(*this, 1, m_bufferSize, dataToUpload, D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS);
	}


	
	D3D12_CPU_DESCRIPTOR_HANDLE DX12ConstantBuffer::GetConstantBufferView(
		const D3D12_CONSTANT_BUFFER_VIEW_DESC* cbvDesc) const
	{
		std::size_t hash = 0;
		if (cbvDesc)
		{
			//TODO FIX this
			//hash = std::hash<D3D12_CONSTANT_BUFFER_VIEW_DESC>(*cbvDesc);
		}

		std::lock_guard<std::mutex> lock(m_ConstantBufferViewsMutex);

		auto iter = m_ConstantBufferViews.find(hash);
		if (iter == m_ConstantBufferViews.end())
		{
			auto srv = CreateConstantBufferView(cbvDesc);
			iter = m_ConstantBufferViews.insert({ hash, std::move(srv) }).first;
		}

		return iter->second.GetDescriptorHandle();
	}

	DescriptorAllocation DX12ConstantBuffer::CreateConstantBufferView(const D3D12_CONSTANT_BUFFER_VIEW_DESC* srvDesc) const
	{

		auto& device = DX12RendererAPI::device;
		auto srv = DX12RendererAPI::Get().AllocateDescriptors(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

		device->CreateConstantBufferView(srvDesc, srv.GetDescriptorHandle());

		return srv;
	}

	void DX12ConstantBuffer::FinishedUploading()
	{
	}

	D3D12_CPU_DESCRIPTOR_HANDLE DX12ConstantBuffer::GetShaderResourceView(
		const D3D12_SHADER_RESOURCE_VIEW_DESC* srvDesc) const
	{
		return D3D12_CPU_DESCRIPTOR_HANDLE();
	}

	D3D12_CPU_DESCRIPTOR_HANDLE DX12ConstantBuffer::GetUnorderedAccessView(
		const D3D12_UNORDERED_ACCESS_VIEW_DESC* uavDesc) const
	{
		return D3D12_CPU_DESCRIPTOR_HANDLE();
	}

	void DX12ConstantBuffer::CreateViews(size_t numElements, size_t elementSize)
	{
	}

	void DX12ConstantBuffer::Upload(void* data, size_t size)
	{
		//memcpy(mappedPtr, data, size);
		dataToUpload = (UINT8*)data;
		DX12RendererAPI::Get().UploadResource(this);
	}
}
