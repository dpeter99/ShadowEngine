#include "shpch.h"
#include "DX12ConstantBuffer.h"
#include "Platform/D3D12/DX12RendererAPI.h"

namespace ShadowEngine::Rendering::D3D12 {
	
	DX12ConstantBuffer::DX12ConstantBuffer(size_t size, std::wstring debug_name): Buffer(debug_name)
	{
		actual_size = (size + 255) & ~255;

		auto desc = CD3DX12_RESOURCE_DESC::Buffer(actual_size);
		
		SetupResource(desc, debug_name);

		m_ConstantBufferView = DX12RendererAPI::Get().AllocateDescriptors(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
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

	/*
	D3D12_GPU_VIRTUAL_ADDRESS DX12ConstantBuffer::GetGPUVirtualAddress() const
	{
		return m_d3d12Resource->GetGPUVirtualAddress();
		
		//return constantBuffer->GetGPUVirtualAddress();
	}
	*/

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
		//cmd->XDEP_UploadToBuffer(*this, 1, m_bufferSize, dataToUpload, D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS);

		cmd->CopyConstantBuffer(*this, this->data_size, this->dataToUpload);
	}

	void DX12ConstantBuffer::FinishedUploading()
	{
	}

	
	/*
	D3D12_CPU_DESCRIPTOR_HANDLE DX12ConstantBuffer::GetConstantBufferView() const
	{
		return m_ConstantBufferView.GetDescriptorHandle();
	}
	*/

	/*
	DescriptorAllocation DX12ConstantBuffer::CreateConstantBufferView(const D3D12_CONSTANT_BUFFER_VIEW_DESC* srvDesc) const
	{

		auto& device = DX12RendererAPI::device;
		auto srv = DX12RendererAPI::Get().AllocateDescriptors(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

		device->CreateConstantBufferView(srvDesc, srv.GetDescriptorHandle());

		return srv;
	}
	*/

	D3D12_CPU_DESCRIPTOR_HANDLE DX12ConstantBuffer::GetShaderResourceView(
		const D3D12_SHADER_RESOURCE_VIEW_DESC* srvDesc) const
	{
		throw std::exception("ConstantBuffer::GetShaderResourceView should not be called.");
	}

	D3D12_CPU_DESCRIPTOR_HANDLE DX12ConstantBuffer::GetUnorderedAccessView(
		const D3D12_UNORDERED_ACCESS_VIEW_DESC* uavDesc) const
	{
		throw std::exception("ConstantBuffer::GetUnorderedAccessView should not be called.");
	}


	void DX12ConstantBuffer::CreateViews(size_t numElements, size_t elementSize)
	{
		data_size = numElements * elementSize;
		actual_size = (data_size + 255) & ~255;

		D3D12_CONSTANT_BUFFER_VIEW_DESC d3d12ConstantBufferViewDesc;
		d3d12ConstantBufferViewDesc.BufferLocation = m_d3d12Resource->GetGPUVirtualAddress();
		d3d12ConstantBufferViewDesc.SizeInBytes = actual_size;

		auto device = DX12RendererAPI::Get().device;

		device->CreateConstantBufferView(&d3d12ConstantBufferViewDesc, m_ConstantBufferView.GetDescriptorHandle());

	}

	D3D12_CPU_DESCRIPTOR_HANDLE DX12ConstantBuffer::GetConstantBufferView(const D3D12_CONSTANT_BUFFER_VIEW_DESC* srvDesc) const
	{
		return m_ConstantBufferView.GetDescriptorHandle();
	}

	void DX12ConstantBuffer::Upload(void* data, size_t size)
	{
		data_size = size;
		actual_size = (size + 255) & ~255;

		dataToUpload = (UINT8*)data;
		DX12RendererAPI::Get().UploadResource(this);
	}
}
