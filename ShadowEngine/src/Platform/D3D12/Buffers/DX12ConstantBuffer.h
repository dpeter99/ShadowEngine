#pragma once
#include "Platform/D3D12/Common.h"
#include "ShadowRenderer/ConstantBuffer.h"
//#include "Platform/D3D12/DX12RendererAPI.h"
#include "Buffer.h"
#include "Platform/D3D12/Descriptors/DescriptorAllocation.h"

namespace ShadowEngine::Rendering::D3D12 {

	/// <summary>
	/// Represents a Constant buffer on the GPU side
	/// </summary>
	///
	/// This is used by the Rendering::ConstantBuffers for the actual implementation
	/// It gets the size of the buffer needed and than the value gets stored in it by using the Upload function
	class DX12ConstantBuffer : public ConstantBufferImpl, public Buffer
	{
		UINT8* dataToUpload;
		
		/// <summary>
		/// The actual size of the buffer aligned to device size increments.
		/// </summary>
		size_t actual_size;

		/// <summary>
		/// The size of the Data that is being copied to the GPU.
		/// </summary>
		size_t data_size;

		//UINT8* mappedPtr;
		//com_ptr<ID3D12Resource> constantBuffer;
		//mutable std::unordered_map<size_t, DescriptorAllocation> m_ConstantBufferViews;
		//mutable std::mutex m_ConstantBufferViewsMutex;

		DescriptorAllocation m_ConstantBufferView;

	private:
		//DescriptorAllocation CreateConstantBufferView(const D3D12_CONSTANT_BUFFER_VIEW_DESC* srvDesc) const;

	public:

		/// <summary>
		/// Constructor for a Constant Buffer.
		/// </summary>
		/// <param name="size"></param>
		/// <param name="debug_name"></param>
		DX12ConstantBuffer(size_t size, std::wstring debug_name);

		~DX12ConstantBuffer();

		//D3D12_GPU_VIRTUAL_ADDRESS GetGPUVirtualAddress() const;
		//void CreateResources(size_t size);
		//void ReleaseResources();

		/// <summary>
		/// Returns the actual size of the resource in the GPU memory.
		/// </summary>
		/// This might be bigger than the size it was created with because DX12 needs the buffers to be alined to 255 bites.
		/// <returns>The actual size</returns>
		size_t GetSize() { return this->actual_size; };
		
		/// <summary>
		/// Uploads the gived data to the GPU.
		/// </summary>
		/// The size must be the same as the size given fro creating the buffer.
		/// <param name="data"></param>
		/// <param name="size"></param>
		void Upload(void* data, size_t size) override;


		//############################
		// IUploadable
		//############################

		void RecordTransfer(ShadowEngine::Ref<CommandList> cmd) override;

		void FinishedUploading() override;



		//D3D12_CPU_DESCRIPTOR_HANDLE GetConstantBufferView() const;


		//############################
		// Resource
		//############################

		D3D12_CPU_DESCRIPTOR_HANDLE
		GetShaderResourceView(const D3D12_SHADER_RESOURCE_VIEW_DESC* srvDesc) const override;

		D3D12_CPU_DESCRIPTOR_HANDLE
		GetUnorderedAccessView(const D3D12_UNORDERED_ACCESS_VIEW_DESC* uavDesc) const override;

		void CreateViews(size_t numElements, size_t elementSize) override;

		// Inherited via Buffer
		virtual D3D12_CPU_DESCRIPTOR_HANDLE GetConstantBufferView(const D3D12_CONSTANT_BUFFER_VIEW_DESC* srvDesc = nullptr) const override;
	};


}
