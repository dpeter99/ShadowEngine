#pragma once
#include "Common.h"
#include "ShadowRenderer/ConstantBuffer.h"
#include "DX12RendererAPI.h"
#include "Buffers/Buffer.h"

namespace ShadowEngine::Rendering::D3D12 {


	/// <summary>
	/// Represents a Constant buffer on the GPU side
	/// </summary>
	///
	/// This is used by the Rendering::ConstantBuffers for the actual implementation
	/// It gets the size of the buffer needed and than the value gets stored in it by using the Upload function
	class DX12ConstantBuffer : public ConstantBufferImpl, public Buffer
	{
		UINT8* mappedPtr;

		UINT8* dataToUpload;
		
		//com_ptr<ID3D12Resource> constantBuffer;

		size_t actual_size;


		mutable std::unordered_map<size_t, DescriptorAllocation> m_ConstantBufferViews;

		mutable std::mutex m_ConstantBufferViewsMutex;
	public:

		DX12ConstantBuffer(size_t size, std::wstring debug_name);

		~DX12ConstantBuffer();

		//void CreateResources(size_t size);

		D3D12_GPU_VIRTUAL_ADDRESS GetGPUVirtualAddress() const;

		//void ReleaseResources();

		size_t GetSize() { return this->actual_size; };
		
		void Upload(void* data, size_t size) override;

		void RecordTransfer(ShadowEngine::Ref<CommandList> cmd) override;

		D3D12_CPU_DESCRIPTOR_HANDLE GetConstantBufferView(const D3D12_CONSTANT_BUFFER_VIEW_DESC* srvDesc) const override;

	private:
		DescriptorAllocation CreateConstantBufferView(const D3D12_CONSTANT_BUFFER_VIEW_DESC* srvDesc) const;
	public:
		void FinishedUploading() override;
		D3D12_CPU_DESCRIPTOR_HANDLE
		GetShaderResourceView(const D3D12_SHADER_RESOURCE_VIEW_DESC* srvDesc) const override;
		D3D12_CPU_DESCRIPTOR_HANDLE
		GetUnorderedAccessView(const D3D12_UNORDERED_ACCESS_VIEW_DESC* uavDesc) const override;
		void CreateViews(size_t numElements, size_t elementSize) override;
	};


}
