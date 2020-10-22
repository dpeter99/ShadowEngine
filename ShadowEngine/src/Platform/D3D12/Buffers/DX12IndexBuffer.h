#pragma once
#include "ShadowRenderer/Buffer.h"
#include "Buffer.h"

#include "ShadowRenderer/DataStructs.h"

namespace ShadowEngine::Rendering::D3D12 {

	class DX12IndexBuffer : public IndexBuffer, public Buffer
	{
		std::vector<uint32_t> indices;

	public:

		/// <summary>
		/// Creates the object but does nothing to allocat or upload anything to the GPU
		/// </summary>
		/// <param name="name">The name of this Buffer</param>
		DX12IndexBuffer(const std::wstring& name = L"");

		/// <summary>
		/// Creates a Buffer with the suplied data.
		/// This data will be uploaded to the GPU in the next cycle
		/// </summary>
		/// <param name="verts">The vertex data</param>
		/// <param name="name">The name of this Buffer</param>
		DX12IndexBuffer(std::vector<uint32_t> indices, const std::wstring& name = L"");


		//#######################
		// IUploadable
		//#######################

		virtual void RecordTransfer(Ref<D3D12::CommandList> cmd) override;

		virtual void FinishedUploading() override;



		virtual D3D12_CPU_DESCRIPTOR_HANDLE GetShaderResourceView(const D3D12_SHADER_RESOURCE_VIEW_DESC* srvDesc = nullptr) const override;

		virtual D3D12_CPU_DESCRIPTOR_HANDLE GetUnorderedAccessView(const D3D12_UNORDERED_ACCESS_VIEW_DESC* uavDesc = nullptr) const override;


		virtual void CreateViews(size_t numElements, size_t elementSize) override;


		virtual D3D12_CPU_DESCRIPTOR_HANDLE GetConstantBufferView(const D3D12_CONSTANT_BUFFER_VIEW_DESC* srvDesc = nullptr) const override;

		// Inherited via IndexBuffer
		virtual uint32_t GetCount() const override;

		// Inherited via IndexBuffer
		virtual void SetName(std::string name) override;
	};
}

