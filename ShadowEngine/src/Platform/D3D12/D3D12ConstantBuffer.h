#pragma once
#include "Common.h"
#include "ShadowRenderer/ConstantBuffer.h"
#include "D3D12RendererAPI.h"

namespace ShadowEngine::Rendering::D3D12 {

	class D3D12ConstantBuffer : public ConstantBufferImpl
	{
		UINT8* mappedPtr;
		com_ptr<ID3D12Resource> constantBuffer;
		
	public:

		D3D12ConstantBuffer(size_t size);

		~D3D12ConstantBuffer();

		void CreateResources(size_t size);

		D3D12_GPU_VIRTUAL_ADDRESS GetGPUVirtualAddress() const;

		void ReleaseResources();

		void Upload(void* data, size_t size) override;
	};


}
