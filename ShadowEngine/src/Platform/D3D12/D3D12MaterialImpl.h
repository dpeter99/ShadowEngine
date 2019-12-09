#pragma once

#include "Common.h"
#include "D3D12DescriptorHeap.h"
#include "ShadowRenderer/ShaderPropertySheet.h"
#include "ShadowRenderer/ConstantBuffer.h"
#include "D3D12RendererAPI.h"
#include "D3D12ConstantBuffer.h"
//#include "ShadowRenderer/MaterialImpl.h"

namespace  ShadowEngine::Rendering::D3D12 {


	//This should hold the:
	//Constant buffers
	//The textures
	class D3D12MaterialImpl : public Assets::MaterialImpl
	{
		Ref<ShaderPropertySheet> propertySheet;


		Ref<Rendering::ConstantBuffer> shaderData;

		//std::vector<Ref<D3D12Texture2D>> textures;
		
		DescriptorAllocation table;
		


		int rootSigIndex;
	public:
		D3D12MaterialImpl(Ref<ShaderPropertySheet> propertySheet) : propertySheet(propertySheet)
		{
			//Constant Buffer object

			this->shaderData = std::make_shared<Rendering::ConstantBuffer_ShaderPropertySheet>(propertySheet);
			D3D12ConstantBuffer* dx12_buffer = ((D3D12ConstantBuffer*)shaderData->GetImpl().get());
			shaderData->Upload();
			
			
			//Descriptor Table
			table = D3D12RendererAPI::Instance->descriptorHeap_SRV_CBV->Allocate(1+propertySheet->GetTextureCount());
			
			//Constant Buffer descriptor

			D3D12_CONSTANT_BUFFER_VIEW_DESC cbvDesc = {};
			cbvDesc.BufferLocation = dx12_buffer->GetGPUVirtualAddress();
			cbvDesc.SizeInBytes = dx12_buffer->GetSize();    // CB size is required to be 256-byte aligned.
			D3D12RendererAPI::device->CreateConstantBufferView(&cbvDesc, table.CPU_TableStart);

			//Textures Descriptor

			for (size_t i = 0; i < propertySheet->GetTextureCount(); i++)
			{
				auto* prop = propertySheet->GetTexture(i);
				//if(prop->)
				int type = prop->GetPropertyDataTyped().GetTypeId();
				
				D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
				

				if (type == Assets::Texture2D::TypeId()) {
					auto a = std::dynamic_pointer_cast<D3D12::D3D12Texture2D>(prop->GetPropertyDataTyped().getImpl());

					srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
					srvDesc.Format = a->GetDXGIFormat();
					srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
					prop->GetPropertyData();
					srvDesc.Texture2D.MipLevels = 1;
					D3D12RendererAPI::device->CreateShaderResourceView(a->GetResource().Get(), &srvDesc, table[i+1].CPU_TableStart);
				}
				
				
			}
			
			

		}

		void BindMaterialData(Ref<D3D12CommandList> commandList)
		{
			commandList->BindDescriptorTableBuffer(table.GPU_TableStart, 2);
		}

		void Upload() override
		{
			shaderData->Upload();
		}

		void UploadTextures() {

			//TODO: This will not work once we have more than one command list and back buffering of commands
			for (size_t i = 1; i < propertySheet->GetTextureCount() + 1; i++)
			{
				auto* prop = propertySheet->GetTexture(i);

				int type = prop->GetPropertyDataTyped().GetTypeId();

				D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {};


				if (type == Assets::Texture2D::TypeId()) {
					auto a = std::dynamic_pointer_cast<D3D12::D3D12Texture2D>(prop->GetPropertyDataTyped().getImpl());

					srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
					srvDesc.Format = a->GetDXGIFormat();
					srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
					prop->GetPropertyData();
					srvDesc.Texture2D.MipLevels = 1;
					D3D12RendererAPI::device->CreateShaderResourceView(a->GetResource().Get(), &srvDesc, table[i].CPU_TableStart);
				}


			}
		}
	};

}

