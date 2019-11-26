#pragma once

#include "Common.h"
#include "D3D12DescriptorHeap.h"
#include "ShadowRenderer/ShaderPropertySheet.h"
#include "ShadowRenderer/ConstantBuffer.h"
#include "D3D12RendererAPI.h"
#include "D3D12ConstantBuffer.h"
#include "ShadowRenderer/MaterialImpl.h"

namespace  ShadowEngine::Rendering::D3D12 {


	//This should hold the:
	//Constant buffers
	//The textures
	class D3D12MaterialImpl : public Assets::MaterialImpl
	{

		Ref<Rendering::ConstantBuffer> shaderData;

		std::vector<Ref<D3D12Texture>> textures;
		
		DescriptorAllocation table;
		
		int rootSigIndex;
	public:
		D3D12MaterialImpl(Ref<ShaderPropertySheet> propertySheet)
		{
			this->shaderData = std::make_shared<Rendering::ConstantBuffer_ShaderPropertySheet>(propertySheet);
			D3D12ConstantBuffer* dx12_buffer = ((D3D12ConstantBuffer*)shaderData->GetImpl().get());

			
			table = D3D12RendererAPI::Instance->descriptorHeap_SRV_CBV->Allocate(1);
			
			/*
			D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
			srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
			srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
			srvDesc.Format = textures[0]->GetDXGIFormat();
			srvDesc.Texture2D.MipLevels = 0;
			srvDesc.Texture2D.MostDetailedMip = 0;
			srvDesc.Texture2D.ResourceMinLODClamp = 0.0f;
			D3D12RendererAPI::device->CreateShaderResourceView(textures[0]->GetResource().Get(), &srvDesc, tableStart);

			tableStart.Offset(1, D3D12RendererAPI::Instance->descriptorHeap_SRV_CBV->GetOffsetSize());
			*/
			D3D12_CONSTANT_BUFFER_VIEW_DESC cbvDesc = {};
			cbvDesc.BufferLocation = dx12_buffer->GetGPUVirtualAddress();
			cbvDesc.SizeInBytes = (propertySheet->GetSize() + 255) & ~255;    // CB size is required to be 256-byte aligned.
			D3D12RendererAPI::device->CreateConstantBufferView(&cbvDesc, table.CPU_TableStart);
		}

		void BindMaterialData(Ref<D3D12CommandList> commandList)
		{
			commandList->BindDescriptorTableBuffer(table.GPU_TableStart, 0);
		}

		void Upload() override
		{
			shaderData->Upload();
		}
	};

}

