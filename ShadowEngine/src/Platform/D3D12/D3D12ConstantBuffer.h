#pragma once
#include "Common.h"
#include "ShadowRenderer/ConstantBuffer.h"
#include "DX12RendererAPI.h"
#include "Buffers/Buffer.h"

namespace ShadowEngine::Rendering::D3D12 {

	class DX12ConstantBuffer : public ConstantBufferImpl, public Buffer
	{
		UINT8* mappedPtr;
		//com_ptr<ID3D12Resource> constantBuffer;

		//size_t actual_size;

		//std::wstring debug_name;
	public:

		DX12ConstantBuffer(size_t size, std::wstring debug_name);

		~DX12ConstantBuffer();

		void CreateResources(size_t size);

		D3D12_GPU_VIRTUAL_ADDRESS GetGPUVirtualAddress() const;

		void ReleaseResources();

		size_t GetSize() { return actual_size; };
		
		void Upload(void* data, size_t size) override;
	};


}
